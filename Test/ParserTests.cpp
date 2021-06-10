#include "catch.hpp"
#include "CompilerTest.h"

TEST_CASE("Parser arithmetic", "[Parser]") {
    PARSER_TEST("Arithmetic/SimpleSum")
    PARSER_TEST("Arithmetic/MultipleSum")
    PARSER_TEST("Arithmetic/SumAndProd")
    PARSER_TEST("Arithmetic/ProdAndSum")
    PARSER_TEST("Arithmetic/SumParens")
    PARSER_TEST("Arithmetic/SumAndProd")
    PARSER_TEST("Arithmetic/ComplexSumProd")

    PARSER_TEST("Arithmetic/SumSubProdDiv")
    PARSER_TEST("Arithmetic/ComplexTest1")

    PARSER_TEST("Arithmetic/UnaryOperation1")
    PARSER_TEST("Arithmetic/UnaryOperation2")
    PARSER_TEST("Arithmetic/DoubleUnary")
    PARSER_TEST("Arithmetic/ComplexUnaryOperation")

    PARSER_TEST("Arithmetic/Identifiers")

    PARSER_TEST("Arithmetic/UnclosedParenError")
    PARSER_TEST("Arithmetic/UnexpectedLexemeError1")
    PARSER_TEST("Arithmetic/UnexpectedLexemeError2")
    PARSER_TEST("Arithmetic/ErrorNumber")

    PARSER_TEST("Arithmetic/InfixOperator")
    PARSER_TEST("Arithmetic/InRangeOperator")
    PARSER_TEST("Arithmetic/BooleanOperators")
}

TEST_CASE("Parser basic syntax", "[Parser]") {
    PARSER_TEST("BasicSyntax/EmptyFun.kt")
    PARSER_TEST("BasicSyntax/FunParams1.kt")
    PARSER_TEST("BasicSyntax/FunParams2.kt")
    PARSER_TEST("BasicSyntax/FunDefaultParams.kt")

    PARSER_TEST("BasicSyntax/MemberAccess1.kt")
    PARSER_TEST("BasicSyntax/MemberAccess2.kt")
    PARSER_TEST("BasicSyntax/PostfixOperators.kt")

    PARSER_TEST("BasicSyntax/ErrorNoFunName.kt")
    PARSER_TEST("BasicSyntax/ErrorNoIndex.kt")
    PARSER_TEST("BasicSyntax/ErrorNoMember.kt")
    PARSER_TEST("BasicSyntax/ErrorNoParamName.kt")
    PARSER_TEST("BasicSyntax/ErrorNoTypeName.kt")
    PARSER_TEST("BasicSyntax/ErrorNoType.kt")
    PARSER_TEST("BasicSyntax/ErrorNoPropName.kt")

    PARSER_TEST("BasicSyntax/PropDecl1.kt")
    PARSER_TEST("BasicSyntax/PropDecl2.kt")
    PARSER_TEST("BasicSyntax/PropDecl3.kt")
    PARSER_TEST("BasicSyntax/PropFunDecl.kt")
}
