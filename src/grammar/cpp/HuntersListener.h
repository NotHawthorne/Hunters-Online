
// Generated from Hunters.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "HuntersParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by HuntersParser.
 */
class  HuntersListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterMain(HuntersParser::MainContext *ctx) = 0;
  virtual void exitMain(HuntersParser::MainContext *ctx) = 0;

  virtual void enterExpr(HuntersParser::ExprContext *ctx) = 0;
  virtual void exitExpr(HuntersParser::ExprContext *ctx) = 0;

  virtual void enterQuery(HuntersParser::QueryContext *ctx) = 0;
  virtual void exitQuery(HuntersParser::QueryContext *ctx) = 0;

  virtual void enterCommand(HuntersParser::CommandContext *ctx) = 0;
  virtual void exitCommand(HuntersParser::CommandContext *ctx) = 0;

  virtual void enterDestination(HuntersParser::DestinationContext *ctx) = 0;
  virtual void exitDestination(HuntersParser::DestinationContext *ctx) = 0;

  virtual void enterChat(HuntersParser::ChatContext *ctx) = 0;
  virtual void exitChat(HuntersParser::ChatContext *ctx) = 0;

  virtual void enterWords(HuntersParser::WordsContext *ctx) = 0;
  virtual void exitWords(HuntersParser::WordsContext *ctx) = 0;

  virtual void enterArg(HuntersParser::ArgContext *ctx) = 0;
  virtual void exitArg(HuntersParser::ArgContext *ctx) = 0;

  virtual void enterQualifier(HuntersParser::QualifierContext *ctx) = 0;
  virtual void exitQualifier(HuntersParser::QualifierContext *ctx) = 0;

  virtual void enterSlot(HuntersParser::SlotContext *ctx) = 0;
  virtual void exitSlot(HuntersParser::SlotContext *ctx) = 0;

  virtual void enterComparison(HuntersParser::ComparisonContext *ctx) = 0;
  virtual void exitComparison(HuntersParser::ComparisonContext *ctx) = 0;

  virtual void enterStat(HuntersParser::StatContext *ctx) = 0;
  virtual void exitStat(HuntersParser::StatContext *ctx) = 0;

  virtual void enterRange(HuntersParser::RangeContext *ctx) = 0;
  virtual void exitRange(HuntersParser::RangeContext *ctx) = 0;


};

