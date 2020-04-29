
// Generated from Hunters.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"
#include "HuntersVisitor.h"


/**
 * This class provides an empty implementation of HuntersVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  HuntersBaseVisitor : public HuntersVisitor {
public:

  virtual antlrcpp::Any visitMain(HuntersParser::MainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpr(HuntersParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitQuery(HuntersParser::QueryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCommand(HuntersParser::CommandContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDestination(HuntersParser::DestinationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitChat(HuntersParser::ChatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWords(HuntersParser::WordsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArg(HuntersParser::ArgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitQualifier(HuntersParser::QualifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSlot(HuntersParser::SlotContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitComparison(HuntersParser::ComparisonContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStat(HuntersParser::StatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRange(HuntersParser::RangeContext *ctx) override {
    return visitChildren(ctx);
  }


};

