{9. Имеется  текстовый  файл  с  некоторым  описанием.   Все
предложения   заканчиваются   точкой.   Требуется   проверить,
является  ли  первая  буква  каждого  предложения   прописной.
Исправить обнаруженные ошибки (6).Красильникова Ольга ПС-21}
PROGRAM DetermineRegister(INPUT, OUTPUT);

FUNCTION BigSymbol(VAR Ch: CHAR): BOOLEAN; {Проверка на принадлежность к прописной букве}
CONST
  BigChar = ['A' .. 'Z', 'А' .. 'Я', 'Ё'];
BEGIN   
  BigSymbol := (Ch IN BigChar)
END;

FUNCTION SmallSymbol(VAR Ch: CHAR): BOOLEAN; {Проверка на принадлежность к строчной букве}
CONST
  SmallChar = ['a' .. 'z', 'а' .. 'я', 'ё'];
BEGIN   
  SmallSymbol := (Ch IN SmallChar)
END;

FUNCTION UpperCase(Ch: CHAR): CHAR;
BEGIN
  CASE Ch OF
    'a'..'z': Ch := CHR(ORD(Ch) - 32);
    'а'..'я': Ch := CHR(ORD(Ch) - 32);
    'ё': Ch := 'Ё'
  END;
  UpperCase := Ch
END;


PROCEDURE FindEnd(VAR F: TEXT; VAR Ch: CHAR);  {Поиск конца предложения}
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

PROCEDURE DetermineRegisterInFile(VAR F: TEXT); {Определяем является ли первая буква каждого предложения прописной}
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
  IF IORESULT <> 0  {Проверка на существование файла} 
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
