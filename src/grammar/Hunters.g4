grammar	Hunters;

main
	: expr '\n'
	;
expr
	: (query | command | chat)*
	;
query
	: QS destination (arg)*
	;
QS
	: ('view' | 'list' | 'give' | 'drop')
	;
command
	: CS destination (arg)*
	| HUNT
	;
CS
	: ('move' | 'equip' | 'inspect' | 'cast')
	;
HUNT
	: 'hunt'
	;
destination
	: STRING
	;
chat
	: CHAS (words)+
	| TELL destination (words)+
	;
TELL
	: ('tell' | 'whisper' | 'dm' | 'pm' | 'message')
	;
CHAS
	: ('say' | 'yell' | 'global' )
	;
words
	: STRING (words)*
	;
arg
	: ', ' qualifier arg?
	;
qualifier
	: (comparison | slot | INT)
	;
slot
	: ('head' | 'shoulders' | 'chest' | 'hands' | 'wrists' | 'waist' | 'legs' | 'feet' | 'finger1' | 'finger2' | 'off-hand' | 'main-hand')
	;
comparison
	: stat CMP INT
	| stat EQ INT
	| stat  EQ range
	| STRING EQ STRING
	;
stat
	: 'strength' | 'dexterity' | 'intellect' | 'lifesteal' | 'chain_lightning' | 'stun' | 'rarity' | 'level' | 'ilvl' | 'health' | 'heal' | 'proc_chance'
	;
CMP
	: ('>=' | '<=' | '>' | '<')
	;
INT
	: [0-9]+
	; 
WS
	: (' ' | '\t' | '\r' | '\n' | '\f')+ -> channel(HIDDEN)
	;
STRING
	: [a-z0-9]+
	;
EQ
	: '='
	;
range
	: INT ':' INT
	;
