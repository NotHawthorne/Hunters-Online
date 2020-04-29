
// Generated from Hunters.g4 by ANTLR 4.7.1


#include "HuntersListener.h"

#include "HuntersParser.h"


using namespace antlrcpp;
using namespace antlr4;

HuntersParser::HuntersParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

HuntersParser::~HuntersParser() {
  delete _interpreter;
}

std::string HuntersParser::getGrammarFileName() const {
  return "Hunters.g4";
}

const std::vector<std::string>& HuntersParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& HuntersParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- MainContext ------------------------------------------------------------------

HuntersParser::MainContext::MainContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HuntersParser::ExprContext* HuntersParser::MainContext::expr() {
  return getRuleContext<HuntersParser::ExprContext>(0);
}


size_t HuntersParser::MainContext::getRuleIndex() const {
  return HuntersParser::RuleMain;
}

void HuntersParser::MainContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMain(this);
}

void HuntersParser::MainContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMain(this);
}

HuntersParser::MainContext* HuntersParser::main() {
  MainContext *_localctx = _tracker.createInstance<MainContext>(_ctx, getState());
  enterRule(_localctx, 0, HuntersParser::RuleMain);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(26);
    expr();
    setState(27);
    match(HuntersParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

HuntersParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HuntersParser::QueryContext *> HuntersParser::ExprContext::query() {
  return getRuleContexts<HuntersParser::QueryContext>();
}

HuntersParser::QueryContext* HuntersParser::ExprContext::query(size_t i) {
  return getRuleContext<HuntersParser::QueryContext>(i);
}

std::vector<HuntersParser::CommandContext *> HuntersParser::ExprContext::command() {
  return getRuleContexts<HuntersParser::CommandContext>();
}

HuntersParser::CommandContext* HuntersParser::ExprContext::command(size_t i) {
  return getRuleContext<HuntersParser::CommandContext>(i);
}

std::vector<HuntersParser::ChatContext *> HuntersParser::ExprContext::chat() {
  return getRuleContexts<HuntersParser::ChatContext>();
}

HuntersParser::ChatContext* HuntersParser::ExprContext::chat(size_t i) {
  return getRuleContext<HuntersParser::ChatContext>(i);
}


size_t HuntersParser::ExprContext::getRuleIndex() const {
  return HuntersParser::RuleExpr;
}

void HuntersParser::ExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr(this);
}

void HuntersParser::ExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr(this);
}

HuntersParser::ExprContext* HuntersParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 2, HuntersParser::RuleExpr);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(34);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << HuntersParser::QS)
      | (1ULL << HuntersParser::CS)
      | (1ULL << HuntersParser::HUNT)
      | (1ULL << HuntersParser::TELL)
      | (1ULL << HuntersParser::CHAS))) != 0)) {
      setState(32);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case HuntersParser::QS: {
          setState(29);
          query();
          break;
        }

        case HuntersParser::CS:
        case HuntersParser::HUNT: {
          setState(30);
          command();
          break;
        }

        case HuntersParser::TELL:
        case HuntersParser::CHAS: {
          setState(31);
          chat();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(36);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QueryContext ------------------------------------------------------------------

HuntersParser::QueryContext::QueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HuntersParser::QueryContext::QS() {
  return getToken(HuntersParser::QS, 0);
}

HuntersParser::DestinationContext* HuntersParser::QueryContext::destination() {
  return getRuleContext<HuntersParser::DestinationContext>(0);
}

std::vector<HuntersParser::ArgContext *> HuntersParser::QueryContext::arg() {
  return getRuleContexts<HuntersParser::ArgContext>();
}

HuntersParser::ArgContext* HuntersParser::QueryContext::arg(size_t i) {
  return getRuleContext<HuntersParser::ArgContext>(i);
}


size_t HuntersParser::QueryContext::getRuleIndex() const {
  return HuntersParser::RuleQuery;
}

void HuntersParser::QueryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterQuery(this);
}

void HuntersParser::QueryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitQuery(this);
}

HuntersParser::QueryContext* HuntersParser::query() {
  QueryContext *_localctx = _tracker.createInstance<QueryContext>(_ctx, getState());
  enterRule(_localctx, 4, HuntersParser::RuleQuery);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(37);
    match(HuntersParser::QS);
    setState(38);
    destination();
    setState(42);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HuntersParser::T__1) {
      setState(39);
      arg();
      setState(44);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CommandContext ------------------------------------------------------------------

HuntersParser::CommandContext::CommandContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HuntersParser::CommandContext::CS() {
  return getToken(HuntersParser::CS, 0);
}

HuntersParser::DestinationContext* HuntersParser::CommandContext::destination() {
  return getRuleContext<HuntersParser::DestinationContext>(0);
}

std::vector<HuntersParser::ArgContext *> HuntersParser::CommandContext::arg() {
  return getRuleContexts<HuntersParser::ArgContext>();
}

HuntersParser::ArgContext* HuntersParser::CommandContext::arg(size_t i) {
  return getRuleContext<HuntersParser::ArgContext>(i);
}

tree::TerminalNode* HuntersParser::CommandContext::HUNT() {
  return getToken(HuntersParser::HUNT, 0);
}


size_t HuntersParser::CommandContext::getRuleIndex() const {
  return HuntersParser::RuleCommand;
}

void HuntersParser::CommandContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCommand(this);
}

void HuntersParser::CommandContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCommand(this);
}

HuntersParser::CommandContext* HuntersParser::command() {
  CommandContext *_localctx = _tracker.createInstance<CommandContext>(_ctx, getState());
  enterRule(_localctx, 6, HuntersParser::RuleCommand);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(54);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HuntersParser::CS: {
        enterOuterAlt(_localctx, 1);
        setState(45);
        match(HuntersParser::CS);
        setState(46);
        destination();
        setState(50);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == HuntersParser::T__1) {
          setState(47);
          arg();
          setState(52);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

      case HuntersParser::HUNT: {
        enterOuterAlt(_localctx, 2);
        setState(53);
        match(HuntersParser::HUNT);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DestinationContext ------------------------------------------------------------------

HuntersParser::DestinationContext::DestinationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HuntersParser::DestinationContext::STRING() {
  return getToken(HuntersParser::STRING, 0);
}


size_t HuntersParser::DestinationContext::getRuleIndex() const {
  return HuntersParser::RuleDestination;
}

void HuntersParser::DestinationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDestination(this);
}

void HuntersParser::DestinationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDestination(this);
}

HuntersParser::DestinationContext* HuntersParser::destination() {
  DestinationContext *_localctx = _tracker.createInstance<DestinationContext>(_ctx, getState());
  enterRule(_localctx, 8, HuntersParser::RuleDestination);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(56);
    match(HuntersParser::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChatContext ------------------------------------------------------------------

HuntersParser::ChatContext::ChatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HuntersParser::ChatContext::CHAS() {
  return getToken(HuntersParser::CHAS, 0);
}

std::vector<HuntersParser::WordsContext *> HuntersParser::ChatContext::words() {
  return getRuleContexts<HuntersParser::WordsContext>();
}

HuntersParser::WordsContext* HuntersParser::ChatContext::words(size_t i) {
  return getRuleContext<HuntersParser::WordsContext>(i);
}

tree::TerminalNode* HuntersParser::ChatContext::TELL() {
  return getToken(HuntersParser::TELL, 0);
}

HuntersParser::DestinationContext* HuntersParser::ChatContext::destination() {
  return getRuleContext<HuntersParser::DestinationContext>(0);
}


size_t HuntersParser::ChatContext::getRuleIndex() const {
  return HuntersParser::RuleChat;
}

void HuntersParser::ChatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChat(this);
}

void HuntersParser::ChatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChat(this);
}

HuntersParser::ChatContext* HuntersParser::chat() {
  ChatContext *_localctx = _tracker.createInstance<ChatContext>(_ctx, getState());
  enterRule(_localctx, 10, HuntersParser::RuleChat);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(71);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HuntersParser::CHAS: {
        enterOuterAlt(_localctx, 1);
        setState(58);
        match(HuntersParser::CHAS);
        setState(60); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(59);
          words();
          setState(62); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == HuntersParser::STRING);
        break;
      }

      case HuntersParser::TELL: {
        enterOuterAlt(_localctx, 2);
        setState(64);
        match(HuntersParser::TELL);
        setState(65);
        destination();
        setState(67); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(66);
          words();
          setState(69); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == HuntersParser::STRING);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WordsContext ------------------------------------------------------------------

HuntersParser::WordsContext::WordsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HuntersParser::WordsContext::STRING() {
  return getToken(HuntersParser::STRING, 0);
}

std::vector<HuntersParser::WordsContext *> HuntersParser::WordsContext::words() {
  return getRuleContexts<HuntersParser::WordsContext>();
}

HuntersParser::WordsContext* HuntersParser::WordsContext::words(size_t i) {
  return getRuleContext<HuntersParser::WordsContext>(i);
}


size_t HuntersParser::WordsContext::getRuleIndex() const {
  return HuntersParser::RuleWords;
}

void HuntersParser::WordsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWords(this);
}

void HuntersParser::WordsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWords(this);
}

HuntersParser::WordsContext* HuntersParser::words() {
  WordsContext *_localctx = _tracker.createInstance<WordsContext>(_ctx, getState());
  enterRule(_localctx, 12, HuntersParser::RuleWords);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(73);
    match(HuntersParser::STRING);
    setState(77);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(74);
        words(); 
      }
      setState(79);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgContext ------------------------------------------------------------------

HuntersParser::ArgContext::ArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HuntersParser::QualifierContext* HuntersParser::ArgContext::qualifier() {
  return getRuleContext<HuntersParser::QualifierContext>(0);
}

HuntersParser::ArgContext* HuntersParser::ArgContext::arg() {
  return getRuleContext<HuntersParser::ArgContext>(0);
}


size_t HuntersParser::ArgContext::getRuleIndex() const {
  return HuntersParser::RuleArg;
}

void HuntersParser::ArgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArg(this);
}

void HuntersParser::ArgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArg(this);
}

HuntersParser::ArgContext* HuntersParser::arg() {
  ArgContext *_localctx = _tracker.createInstance<ArgContext>(_ctx, getState());
  enterRule(_localctx, 14, HuntersParser::RuleArg);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(80);
    match(HuntersParser::T__1);
    setState(81);
    qualifier();
    setState(83);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      setState(82);
      arg();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QualifierContext ------------------------------------------------------------------

HuntersParser::QualifierContext::QualifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HuntersParser::ComparisonContext* HuntersParser::QualifierContext::comparison() {
  return getRuleContext<HuntersParser::ComparisonContext>(0);
}

HuntersParser::SlotContext* HuntersParser::QualifierContext::slot() {
  return getRuleContext<HuntersParser::SlotContext>(0);
}

tree::TerminalNode* HuntersParser::QualifierContext::INT() {
  return getToken(HuntersParser::INT, 0);
}


size_t HuntersParser::QualifierContext::getRuleIndex() const {
  return HuntersParser::RuleQualifier;
}

void HuntersParser::QualifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterQualifier(this);
}

void HuntersParser::QualifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitQualifier(this);
}

HuntersParser::QualifierContext* HuntersParser::qualifier() {
  QualifierContext *_localctx = _tracker.createInstance<QualifierContext>(_ctx, getState());
  enterRule(_localctx, 16, HuntersParser::RuleQualifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(88);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HuntersParser::T__14:
      case HuntersParser::T__15:
      case HuntersParser::T__16:
      case HuntersParser::T__17:
      case HuntersParser::T__18:
      case HuntersParser::T__19:
      case HuntersParser::T__20:
      case HuntersParser::T__21:
      case HuntersParser::T__22:
      case HuntersParser::T__23:
      case HuntersParser::T__24:
      case HuntersParser::T__25:
      case HuntersParser::STRING: {
        setState(85);
        comparison();
        break;
      }

      case HuntersParser::T__2:
      case HuntersParser::T__3:
      case HuntersParser::T__4:
      case HuntersParser::T__5:
      case HuntersParser::T__6:
      case HuntersParser::T__7:
      case HuntersParser::T__8:
      case HuntersParser::T__9:
      case HuntersParser::T__10:
      case HuntersParser::T__11:
      case HuntersParser::T__12:
      case HuntersParser::T__13: {
        setState(86);
        slot();
        break;
      }

      case HuntersParser::INT: {
        setState(87);
        match(HuntersParser::INT);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SlotContext ------------------------------------------------------------------

HuntersParser::SlotContext::SlotContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t HuntersParser::SlotContext::getRuleIndex() const {
  return HuntersParser::RuleSlot;
}

void HuntersParser::SlotContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSlot(this);
}

void HuntersParser::SlotContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSlot(this);
}

HuntersParser::SlotContext* HuntersParser::slot() {
  SlotContext *_localctx = _tracker.createInstance<SlotContext>(_ctx, getState());
  enterRule(_localctx, 18, HuntersParser::RuleSlot);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(90);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << HuntersParser::T__2)
      | (1ULL << HuntersParser::T__3)
      | (1ULL << HuntersParser::T__4)
      | (1ULL << HuntersParser::T__5)
      | (1ULL << HuntersParser::T__6)
      | (1ULL << HuntersParser::T__7)
      | (1ULL << HuntersParser::T__8)
      | (1ULL << HuntersParser::T__9)
      | (1ULL << HuntersParser::T__10)
      | (1ULL << HuntersParser::T__11)
      | (1ULL << HuntersParser::T__12)
      | (1ULL << HuntersParser::T__13))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComparisonContext ------------------------------------------------------------------

HuntersParser::ComparisonContext::ComparisonContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HuntersParser::StatContext* HuntersParser::ComparisonContext::stat() {
  return getRuleContext<HuntersParser::StatContext>(0);
}

tree::TerminalNode* HuntersParser::ComparisonContext::CMP() {
  return getToken(HuntersParser::CMP, 0);
}

tree::TerminalNode* HuntersParser::ComparisonContext::INT() {
  return getToken(HuntersParser::INT, 0);
}

tree::TerminalNode* HuntersParser::ComparisonContext::EQ() {
  return getToken(HuntersParser::EQ, 0);
}

HuntersParser::RangeContext* HuntersParser::ComparisonContext::range() {
  return getRuleContext<HuntersParser::RangeContext>(0);
}

std::vector<tree::TerminalNode *> HuntersParser::ComparisonContext::STRING() {
  return getTokens(HuntersParser::STRING);
}

tree::TerminalNode* HuntersParser::ComparisonContext::STRING(size_t i) {
  return getToken(HuntersParser::STRING, i);
}


size_t HuntersParser::ComparisonContext::getRuleIndex() const {
  return HuntersParser::RuleComparison;
}

void HuntersParser::ComparisonContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComparison(this);
}

void HuntersParser::ComparisonContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComparison(this);
}

HuntersParser::ComparisonContext* HuntersParser::comparison() {
  ComparisonContext *_localctx = _tracker.createInstance<ComparisonContext>(_ctx, getState());
  enterRule(_localctx, 20, HuntersParser::RuleComparison);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(107);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(92);
      stat();
      setState(93);
      match(HuntersParser::CMP);
      setState(94);
      match(HuntersParser::INT);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(96);
      stat();
      setState(97);
      match(HuntersParser::EQ);
      setState(98);
      match(HuntersParser::INT);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(100);
      stat();
      setState(101);
      match(HuntersParser::EQ);
      setState(102);
      range();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(104);
      match(HuntersParser::STRING);
      setState(105);
      match(HuntersParser::EQ);
      setState(106);
      match(HuntersParser::STRING);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatContext ------------------------------------------------------------------

HuntersParser::StatContext::StatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t HuntersParser::StatContext::getRuleIndex() const {
  return HuntersParser::RuleStat;
}

void HuntersParser::StatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStat(this);
}

void HuntersParser::StatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStat(this);
}

HuntersParser::StatContext* HuntersParser::stat() {
  StatContext *_localctx = _tracker.createInstance<StatContext>(_ctx, getState());
  enterRule(_localctx, 22, HuntersParser::RuleStat);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(109);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << HuntersParser::T__14)
      | (1ULL << HuntersParser::T__15)
      | (1ULL << HuntersParser::T__16)
      | (1ULL << HuntersParser::T__17)
      | (1ULL << HuntersParser::T__18)
      | (1ULL << HuntersParser::T__19)
      | (1ULL << HuntersParser::T__20)
      | (1ULL << HuntersParser::T__21)
      | (1ULL << HuntersParser::T__22)
      | (1ULL << HuntersParser::T__23)
      | (1ULL << HuntersParser::T__24)
      | (1ULL << HuntersParser::T__25))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RangeContext ------------------------------------------------------------------

HuntersParser::RangeContext::RangeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> HuntersParser::RangeContext::INT() {
  return getTokens(HuntersParser::INT);
}

tree::TerminalNode* HuntersParser::RangeContext::INT(size_t i) {
  return getToken(HuntersParser::INT, i);
}


size_t HuntersParser::RangeContext::getRuleIndex() const {
  return HuntersParser::RuleRange;
}

void HuntersParser::RangeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRange(this);
}

void HuntersParser::RangeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HuntersListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRange(this);
}

HuntersParser::RangeContext* HuntersParser::range() {
  RangeContext *_localctx = _tracker.createInstance<RangeContext>(_ctx, getState());
  enterRule(_localctx, 24, HuntersParser::RuleRange);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(111);
    match(HuntersParser::INT);
    setState(112);
    match(HuntersParser::T__26);
    setState(113);
    match(HuntersParser::INT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> HuntersParser::_decisionToDFA;
atn::PredictionContextCache HuntersParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN HuntersParser::_atn;
std::vector<uint16_t> HuntersParser::_serializedATN;

std::vector<std::string> HuntersParser::_ruleNames = {
  "main", "expr", "query", "command", "destination", "chat", "words", "arg", 
  "qualifier", "slot", "comparison", "stat", "range"
};

std::vector<std::string> HuntersParser::_literalNames = {
  "", "'\n'", "', '", "'head'", "'shoulders'", "'chest'", "'hands'", "'wrists'", 
  "'waist'", "'legs'", "'feet'", "'finger1'", "'finger2'", "'off-hand'", 
  "'main-hand'", "'strength'", "'dexterity'", "'intellect'", "'lifesteal'", 
  "'chain_lightning'", "'stun'", "'rarity'", "'level'", "'ilvl'", "'health'", 
  "'heal'", "'proc_chance'", "':'", "", "", "'hunt'", "", "", "", "", "", 
  "", "'='"
};

std::vector<std::string> HuntersParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "QS", "CS", "HUNT", "TELL", "CHAS", 
  "CMP", "INT", "WS", "STRING", "EQ"
};

dfa::Vocabulary HuntersParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> HuntersParser::_tokenNames;

HuntersParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x27, 0x76, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 0x3, 0x23, 
    0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x26, 0xb, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x7, 0x4, 0x2b, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x2e, 0xb, 0x4, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 0x5, 0x33, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 
    0x36, 0xb, 0x5, 0x3, 0x5, 0x5, 0x5, 0x39, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x7, 0x3, 0x7, 0x6, 0x7, 0x3f, 0xa, 0x7, 0xd, 0x7, 0xe, 0x7, 0x40, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x6, 0x7, 0x46, 0xa, 0x7, 0xd, 0x7, 0xe, 
    0x7, 0x47, 0x5, 0x7, 0x4a, 0xa, 0x7, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0x4e, 
    0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x51, 0xb, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x5, 0x9, 0x56, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 
    0x5b, 0xa, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0x6e, 0xa, 0xc, 
    0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 
    0x2, 0x2, 0xf, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 
    0x16, 0x18, 0x1a, 0x2, 0x4, 0x3, 0x2, 0x5, 0x10, 0x3, 0x2, 0x11, 0x1c, 
    0x2, 0x78, 0x2, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x4, 0x24, 0x3, 0x2, 0x2, 
    0x2, 0x6, 0x27, 0x3, 0x2, 0x2, 0x2, 0x8, 0x38, 0x3, 0x2, 0x2, 0x2, 0xa, 
    0x3a, 0x3, 0x2, 0x2, 0x2, 0xc, 0x49, 0x3, 0x2, 0x2, 0x2, 0xe, 0x4b, 
    0x3, 0x2, 0x2, 0x2, 0x10, 0x52, 0x3, 0x2, 0x2, 0x2, 0x12, 0x5a, 0x3, 
    0x2, 0x2, 0x2, 0x14, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x16, 0x6d, 0x3, 0x2, 
    0x2, 0x2, 0x18, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x71, 0x3, 0x2, 0x2, 
    0x2, 0x1c, 0x1d, 0x5, 0x4, 0x3, 0x2, 0x1d, 0x1e, 0x7, 0x3, 0x2, 0x2, 
    0x1e, 0x3, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x23, 0x5, 0x6, 0x4, 0x2, 0x20, 
    0x23, 0x5, 0x8, 0x5, 0x2, 0x21, 0x23, 0x5, 0xc, 0x7, 0x2, 0x22, 0x1f, 
    0x3, 0x2, 0x2, 0x2, 0x22, 0x20, 0x3, 0x2, 0x2, 0x2, 0x22, 0x21, 0x3, 
    0x2, 0x2, 0x2, 0x23, 0x26, 0x3, 0x2, 0x2, 0x2, 0x24, 0x22, 0x3, 0x2, 
    0x2, 0x2, 0x24, 0x25, 0x3, 0x2, 0x2, 0x2, 0x25, 0x5, 0x3, 0x2, 0x2, 
    0x2, 0x26, 0x24, 0x3, 0x2, 0x2, 0x2, 0x27, 0x28, 0x7, 0x1e, 0x2, 0x2, 
    0x28, 0x2c, 0x5, 0xa, 0x6, 0x2, 0x29, 0x2b, 0x5, 0x10, 0x9, 0x2, 0x2a, 
    0x29, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x2a, 
    0x3, 0x2, 0x2, 0x2, 0x2c, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x7, 0x3, 
    0x2, 0x2, 0x2, 0x2e, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x30, 0x7, 0x1f, 
    0x2, 0x2, 0x30, 0x34, 0x5, 0xa, 0x6, 0x2, 0x31, 0x33, 0x5, 0x10, 0x9, 
    0x2, 0x32, 0x31, 0x3, 0x2, 0x2, 0x2, 0x33, 0x36, 0x3, 0x2, 0x2, 0x2, 
    0x34, 0x32, 0x3, 0x2, 0x2, 0x2, 0x34, 0x35, 0x3, 0x2, 0x2, 0x2, 0x35, 
    0x39, 0x3, 0x2, 0x2, 0x2, 0x36, 0x34, 0x3, 0x2, 0x2, 0x2, 0x37, 0x39, 
    0x7, 0x20, 0x2, 0x2, 0x38, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x38, 0x37, 0x3, 
    0x2, 0x2, 0x2, 0x39, 0x9, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x3b, 0x7, 0x26, 
    0x2, 0x2, 0x3b, 0xb, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3e, 0x7, 0x22, 0x2, 
    0x2, 0x3d, 0x3f, 0x5, 0xe, 0x8, 0x2, 0x3e, 0x3d, 0x3, 0x2, 0x2, 0x2, 
    0x3f, 0x40, 0x3, 0x2, 0x2, 0x2, 0x40, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x40, 
    0x41, 0x3, 0x2, 0x2, 0x2, 0x41, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x42, 0x43, 
    0x7, 0x21, 0x2, 0x2, 0x43, 0x45, 0x5, 0xa, 0x6, 0x2, 0x44, 0x46, 0x5, 
    0xe, 0x8, 0x2, 0x45, 0x44, 0x3, 0x2, 0x2, 0x2, 0x46, 0x47, 0x3, 0x2, 
    0x2, 0x2, 0x47, 0x45, 0x3, 0x2, 0x2, 0x2, 0x47, 0x48, 0x3, 0x2, 0x2, 
    0x2, 0x48, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x49, 0x3c, 0x3, 0x2, 0x2, 0x2, 
    0x49, 0x42, 0x3, 0x2, 0x2, 0x2, 0x4a, 0xd, 0x3, 0x2, 0x2, 0x2, 0x4b, 
    0x4f, 0x7, 0x26, 0x2, 0x2, 0x4c, 0x4e, 0x5, 0xe, 0x8, 0x2, 0x4d, 0x4c, 
    0x3, 0x2, 0x2, 0x2, 0x4e, 0x51, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x4d, 0x3, 
    0x2, 0x2, 0x2, 0x4f, 0x50, 0x3, 0x2, 0x2, 0x2, 0x50, 0xf, 0x3, 0x2, 
    0x2, 0x2, 0x51, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x52, 0x53, 0x7, 0x4, 0x2, 
    0x2, 0x53, 0x55, 0x5, 0x12, 0xa, 0x2, 0x54, 0x56, 0x5, 0x10, 0x9, 0x2, 
    0x55, 0x54, 0x3, 0x2, 0x2, 0x2, 0x55, 0x56, 0x3, 0x2, 0x2, 0x2, 0x56, 
    0x11, 0x3, 0x2, 0x2, 0x2, 0x57, 0x5b, 0x5, 0x16, 0xc, 0x2, 0x58, 0x5b, 
    0x5, 0x14, 0xb, 0x2, 0x59, 0x5b, 0x7, 0x24, 0x2, 0x2, 0x5a, 0x57, 0x3, 
    0x2, 0x2, 0x2, 0x5a, 0x58, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x59, 0x3, 0x2, 
    0x2, 0x2, 0x5b, 0x13, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5d, 0x9, 0x2, 0x2, 
    0x2, 0x5d, 0x15, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x5f, 0x5, 0x18, 0xd, 0x2, 
    0x5f, 0x60, 0x7, 0x23, 0x2, 0x2, 0x60, 0x61, 0x7, 0x24, 0x2, 0x2, 0x61, 
    0x6e, 0x3, 0x2, 0x2, 0x2, 0x62, 0x63, 0x5, 0x18, 0xd, 0x2, 0x63, 0x64, 
    0x7, 0x27, 0x2, 0x2, 0x64, 0x65, 0x7, 0x24, 0x2, 0x2, 0x65, 0x6e, 0x3, 
    0x2, 0x2, 0x2, 0x66, 0x67, 0x5, 0x18, 0xd, 0x2, 0x67, 0x68, 0x7, 0x27, 
    0x2, 0x2, 0x68, 0x69, 0x5, 0x1a, 0xe, 0x2, 0x69, 0x6e, 0x3, 0x2, 0x2, 
    0x2, 0x6a, 0x6b, 0x7, 0x26, 0x2, 0x2, 0x6b, 0x6c, 0x7, 0x27, 0x2, 0x2, 
    0x6c, 0x6e, 0x7, 0x26, 0x2, 0x2, 0x6d, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x6d, 
    0x62, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x66, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6a, 
    0x3, 0x2, 0x2, 0x2, 0x6e, 0x17, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x70, 0x9, 
    0x3, 0x2, 0x2, 0x70, 0x19, 0x3, 0x2, 0x2, 0x2, 0x71, 0x72, 0x7, 0x24, 
    0x2, 0x2, 0x72, 0x73, 0x7, 0x1d, 0x2, 0x2, 0x73, 0x74, 0x7, 0x24, 0x2, 
    0x2, 0x74, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xe, 0x22, 0x24, 0x2c, 0x34, 0x38, 
    0x40, 0x47, 0x49, 0x4f, 0x55, 0x5a, 0x6d, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

HuntersParser::Initializer HuntersParser::_init;
