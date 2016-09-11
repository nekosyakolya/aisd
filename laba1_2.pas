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


PROCEDURE SearchEnd(VAR F: TEXT; VAR Ch: CHAR);  {����� ����� �����������}
VAR
  EndOffers: CHAR;
BEGIN 
  EndOffers := '.';
  WHILE (NOT EOF(F)) AND (Ch <> EndOffers)
  DO
    READ(F, Ch)
END;

PROCEDURE DetermineRegisterInFile(VAR F: TEXT); {���������� �������� �� ������ ����� ������� ����������� ���������}
TYPE
  MessageArray = ARRAY['0'..'4'] OF STRING;
VAR
  Ch, Switch: CHAR;
  Answer: MessageArray;
  FirstEmptyLine: BOOLEAN;
BEGIN 
  FirstEmptyLine := FALSE;
  Answer['0'] := "������ ����!";
  Answer['1'] := "����������� �������� ������ ����� �����������!";
  Answer['2'] := "������ ����� ����������� ���������!";
  Answer['3'] := "������ ������";
  Answer['4'] := "������ �������� �����!";
  {$I-}
  RESET(F);
  {$I+}
  IF IORESULT <> 0  {�������� �� ������������� �����} 
  THEN
    Switch := '4'
  ELSE
    BEGIN
      Switch := '0';
      WHILE (NOT EOF(F)) AND (Switch <> '1')
      DO
        BEGIN
          IF NOT EOLN(F)
          THEN
            BEGIN
              READ(F, Ch);
              IF BigSymbol(Ch)
              THEN
                BEGIN
                  Switch := '2';
                  SearchEnd(F, Ch)
                END
              ELSE
                IF SmallSymbol(Ch)
                THEN
                  Switch := '1'
            END
          ELSE
            BEGIN
              READLN(F);
              IF NOT FirstEmptyLine
              THEN
                BEGIN
                  FirstEmptyLine := TRUE;
                  Switch :=  '3'
                END
            END
        END;
      CLOSE(F)
    END;
  WRITELN(Answer[Switch])
END;

BEGIN
  DetermineRegisterInFile(INPUT)
END.
