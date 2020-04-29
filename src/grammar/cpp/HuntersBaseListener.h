
// Generated from Hunters.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "HuntersListener.h"


/**
 * This class provides an empty implementation of HuntersListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  HuntersBaseListener : public HuntersListener {
public:

  virtual void enterMain(HuntersParser::MainContext * /*ctx*/) override { }
  virtual void exitMain(HuntersParser::MainContext * /*ctx*/) override { }

  virtual void enterExpr(HuntersParser::ExprContext * /*ctx*/) override { }
  virtual void exitExpr(HuntersParser::ExprContext * /*ctx*/) override { }

  virtual void enterQuery(HuntersParser::QueryContext * /*ctx*/) override { }
  virtual void exitQuery(HuntersParser::QueryContext * /*ctx*/) override { }

  virtual void enterCommand(HuntersParser::CommandContext * /*ctx*/) override { }
  virtual void exitCommand(HuntersParser::CommandContext * /*ctx*/) override { }

  virtual void enterDestination(HuntersParser::DestinationContext * /*ctx*/) override { }
  virtual void exitDestination(HuntersParser::DestinationContext * /*ctx*/) override { }

  virtual void enterChat(HuntersParser::ChatContext * /*ctx*/) override { }
  virtual void exitChat(HuntersParser::ChatContext * /*ctx*/) override { }

  virtual void enterWords(HuntersParser::WordsContext * /*ctx*/) override { }
  virtual void exitWords(HuntersParser::WordsContext * /*ctx*/) override { }

  virtual void enterArg(HuntersParser::ArgContext * /*ctx*/) override { }
  virtual void exitArg(HuntersParser::ArgContext * /*ctx*/) override { }

  virtual void enterQualifier(HuntersParser::QualifierContext * /*ctx*/) override { }
  virtual void exitQualifier(HuntersParser::QualifierContext * /*ctx*/) override { }

  virtual void enterSlot(HuntersParser::SlotContext * /*ctx*/) override { }
  virtual void exitSlot(HuntersParser::SlotContext * /*ctx*/) override { }

  virtual void enterComparison(HuntersParser::ComparisonContext * /*ctx*/) override { }
  virtual void exitComparison(HuntersParser::ComparisonContext * /*ctx*/) override { }

  virtual void enterStat(HuntersParser::StatContext * /*ctx*/) override { }
  virtual void exitStat(HuntersParser::StatContext * /*ctx*/) override { }

  virtual void enterRange(HuntersParser::RangeContext * /*ctx*/) override { }
  virtual void exitRange(HuntersParser::RangeContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

