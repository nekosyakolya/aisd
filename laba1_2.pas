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


PROCEDURE SearchEnd(VAR F: TEXT; VAR Ch: CHAR);  {Поиск конца предложения}
VAR
  EndOffers: CHAR;
BEGIN 
  EndOffers := '.';
  WHILE (NOT EOF(F)) AND (Ch <> EndOffers)
  DO
    READ(F, Ch)
END;

PROCEDURE DetermineRegisterInFile(VAR F: TEXT); {Определяем является ли первая буква каждого предложения прописной}
TYPE
  MessageArray = ARRAY['0'..'4'] OF STRING;
VAR
  Ch, Switch: CHAR;
  Answer: MessageArray;
  FirstEmptyLine: BOOLEAN;
BEGIN 
  FirstEmptyLine := FALSE;
  Answer['0'] := "Пустой файл!";
  Answer['1'] := "Встретилась строчная первая буква предложения!";
  Answer['2'] := "Первые буквы предложений прописные!";
  Answer['3'] := "Пустая строка";
  Answer['4'] := "Ошибка открытия файла!";
  {$I-}
  RESET(F);
  {$I+}
  IF IORESULT <> 0  {Проверка на существование файла} 
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
