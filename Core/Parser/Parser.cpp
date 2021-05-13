#include "Parser.h"

#include "OperationNode.h"
#include "ParserUtils.h"
#include "SimpleNodes.h"

Parser::Parser(Lexer& lexer) : myLexer(lexer) {
    myLexer.NextLexeme();
}

Lexer& Parser::GetLexer() {
    return myLexer;
}

Pointer<ISyntaxNode> Parser::Parse() {
    if (myLexer.GetLexeme().GetType() == Lexeme::LexemeType::EndOfFile) {
        return nullptr;
    }

    Pointer<ISyntaxNode> root = ParseLeftRecursive(0);
    return root;
}

// LeftRecursive(n+1) | LeftRecursive(n+1) operator(n) LeftRecursive(n+1)
Pointer<ISyntaxNode> Parser::ParseLeftRecursive(size_t priority) {
    if (priority == ParserUtils::OperationsPriority.size()) {
        return ParseFactor();
    }

    Pointer<ISyntaxNode> leftOperand = ParseLeftRecursive(priority + 1);
    Lexeme operation = myLexer.GetLexeme();
    while (ParserUtils::OperationsPriority.at(priority).count(operation.GetType())) {
        myLexer.NextLexeme();
        Pointer<ISyntaxNode> rightOperand = ParseLeftRecursive(priority + 1);

        leftOperand = std::make_unique<BinOperationNode>(BinOperationNode(operation, std::move(leftOperand), std::move(rightOperand)));
        operation = myLexer.GetLexeme();
    }

    return leftOperand;
}

// Identifier | Number | UnaryOp Factor
Pointer<ISyntaxNode> Parser::ParseFactor() {
    const Lexeme curLexeme = myLexer.NextLexeme();
    if (curLexeme.GetType() == Lexeme::LexemeType::Identifier) {
        return std::make_unique<IdentifierNode>(IdentifierNode(curLexeme));
    }

    if (LexerUtils::IsIntegerType(curLexeme.GetType())) {
        return std::make_unique<IntegerNode>(IntegerNode(curLexeme));
    }

    if (curLexeme.GetType() == Lexeme::LexemeType::LParen) {
        Pointer<ISyntaxNode> expr = ParseLeftRecursive(0);
        const Lexeme rParen = myLexer.GetLexeme();
        if (rParen.GetType() != Lexeme::LexemeType::RParen) {
            AddError(*expr, rParen, "Expecting \")\"");
        }

        myLexer.NextLexeme();
        return expr;
    }

    if (curLexeme.GetType() == Lexeme::LexemeType::OpSub) {
        Pointer<ISyntaxNode> operand = ParseFactor();
        return std::make_unique<UnaryOperationNode>(UnaryOperationNode(curLexeme, std::move(operand)));
    }

    return std::make_unique<UnexpectedNode>(UnexpectedNode(curLexeme));
}

void Parser::AddError(ISyntaxNode& root, const Lexeme& location, const std::string& error) const {
    root.AddError(std::make_unique<ErrorNode>(ErrorNode(error, location.GetRow(), location.GetColumn())));
}
