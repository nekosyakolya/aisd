{9. �������  ���������  ����  �  ���������  ���������.   ���
�����������   �������������   ������.   ���������   ���������,
��������  ��  ������  �����  �������  �����������   ���������.
��������� ������������ ������ (6).������������� ����� ��-21}
PROGRAM DetermineRegister(INPUT, OUTPUT);

FUNCTION BigSymbol(VAR Ch: CHAR): BOOLEAN; {�������� �� �������������� � ��������� �����}
CONST
  BigChar = ['A' .. 'Z', '�' .. '�', '�'];
BEGIN   
  BigSymbol := (Ch IN BigChar)
END;

FUNCTION SmallSymbol(VAR Ch: CHAR): BOOLEAN; {�������� �� �������������� � �������� �����}
CONST
  SmallChar = ['a' .. 'z', '�' .. '�', '�'];
BEGIN   
  SmallSymbol := (Ch IN SmallChar)
END;

FUNCTION UpperCase(Ch: CHAR): CHAR;
BEGIN
  CASE Ch OF
    'a'..'z': Ch := CHR(ORD(Ch) - 32);
    '�'..'�': Ch := CHR(ORD(Ch) - 32);
    '�': Ch := '�'
  END;
  UpperCase := Ch
END;


PROCEDURE FindEnd(VAR F: TEXT; VAR Ch: CHAR);  {����� ����� �����������}
VAR
  EndOffers: CHAR;
BEGIN 
  EndOffers := '.';
  WHILE (NOT EOF(F)) AND (Ch <> EndOffers)
  DO
    BEGIN
      IF NOT EOLN(F)
      THEN
        BEGIN
          READ(F, Ch);
          WRITE(Ch)
        END
      ELSE
        BEGIN
          READLN(F);
          WRITELN
        END
    END
END;

PROCEDURE DetermineRegisterInFile(VAR F: TEXT); {���������� �������� �� ������ ����� ������� ����������� ���������}
TYPE
  MessageArray = ARRAY['0'..'2'] OF STRING;
VAR
  Ch, Switch: CHAR;
  Answer: MessageArray;
  EndOfSentence: BOOLEAN;
BEGIN 
  EndOfSentence := TRUE;
  Answer['0'] := "Empty files!";
  Answer['1'] := "Error open files!";
  Answer['2'] := "";
  {$I-}
  RESET(F);
  {$I+}
  IF IORESULT <> 0  {�������� �� ������������� �����} 
  THEN
    Switch := '1'
  ELSE
    BEGIN
      Switch := '0';
      WHILE (NOT EOF(F))
      DO
        BEGIN
          IF NOT EOLN(F)
          THEN
            BEGIN
              READ(F, Ch);
              IF SmallSymbol(Ch)
              THEN
                Ch := UpperCase(Ch);
              IF BigSymbol(Ch)
              THEN
                EndOfSentence := FALSE;
              WRITE(Ch);
              IF NOT EndOfSentence
              THEN
                BEGIN
                  FindEnd(F, Ch);
                  EndOfSentence := TRUE
                END
            END
          ELSE
            BEGIN
              READLN(F);
              WRITELN
            END;
          Switch := '2'
        END;
      CLOSE(F)
    END;
  WRITELN(Answer[Switch])
END;

BEGIN
  DetermineRegisterInFile(INPUT)
END.
