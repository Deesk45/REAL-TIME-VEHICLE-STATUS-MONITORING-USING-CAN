#define SETBIT(WORD,SBP) (WORD |= (1<<SBP))
#define CLRBIT(WORD,SBP) (WORD &=~ (1<<SBP))
#define CPLBIT(WORD,SBP) (WORD ^= (1<<SBP))

#define READBIT(WORD,SBP) ((WORD>>SBP) & 1)

#define WRITEBIT(WORD,SBP,BIT) WORD =((WORD &~ (1 << SBP)) | (BIT << SBP))
#define WRITEBYTE(WORD,SBP,BYTE_D) WORD =((WORD&~(0xff << SBP))|(BYTE_D << SBP))
#define WRITENIBBLE(WORD,SBP,NIBBLE) WORD=((WORD&~(0xf << SBP))|(NIBBLE << SBP))
#define WRITEHWORD(WORD,SBP,HWORD) WORD=((WORD&~(0xffff << SBP))|(HWORD << SBP))
