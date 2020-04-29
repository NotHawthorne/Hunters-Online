
// Generated from Hunters.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "HuntersParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by HuntersParser.
 */
class  HuntersVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by HuntersParser.
   */
    virtual antlrcpp::Any visitMain(HuntersParser::MainContext *context) = 0;

    virtual antlrcpp::Any visitExpr(HuntersParser::ExprContext *context) = 0;

    virtual antlrcpp::Any visitQuery(HuntersParser::QueryContext *context) = 0;

    virtual antlrcpp::Any visitCommand(HuntersParser::CommandContext *context) = 0;

    virtual antlrcpp::Any visitDestination(HuntersParser::DestinationContext *context) = 0;

    virtual antlrcpp::Any visitChat(HuntersParser::ChatContext *context) = 0;

    virtual antlrcpp::Any visitWords(HuntersParser::WordsContext *context) = 0;

    virtual antlrcpp::Any visitArg(HuntersParser::ArgContext *context) = 0;

    virtual antlrcpp::Any visitQualifier(HuntersParser::QualifierContext *context) = 0;

    virtual antlrcpp::Any visitSlot(HuntersParser::SlotContext *context) = 0;

    virtual antlrcpp::Any visitComparison(HuntersParser::ComparisonContext *context) = 0;

    virtual antlrcpp::Any visitStat(HuntersParser::StatContext *context) = 0;

    virtual antlrcpp::Any visitRange(HuntersParser::RangeContext *context) = 0;


};

