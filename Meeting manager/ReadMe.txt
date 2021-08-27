Это приложение служит для назначения встреч и вывода данных о встречах в определённый день.
Модель выглядит следующим образом:
	Ввод:
		n - количество запросов
		first_query DataForQuery...
		second_query...
		...

О запросах:
	Есть лишь 2 типа запросов:
		APPOINT - назначить встречу.
		PRINT - вывести информацию о встречах в определённый день, в которых
				участвует определённый человек.

	Об APPOINT:
		Если встречу назначить можно, система выдаёт "OK".
		Если встречу назначить нельзя, система выдаёт "FAIL" и 
			выводит список участников неудавшейся встречи.
		Модель запроса:
			APPOINT day time(hour:min) duration number_of_people first_name ...

	Об PRINT:
		Если информация о встречах есть - она выводится, иначе запрос игнорируется.
		Модель запроса:
			PRINT day name

Пример ввода:
	7
	APPOINT 1 12:30 30 2 andrey alex
	APPOINT 1 12:00 30 2 alex sergey
	APPOINT 1 12:59 60 2 alex andrey
	PRINT 1 alex
	PRINT 1 andrey
	PRINT 1 sergey
	PRINT 2 alex

Пример вывода:
	OK
	OK
	FAIL
	alex andrey
	12:00 30 alex sergey
	12:30 30 andrey alex
	12:30 30 andrey alex
	12:00 30 alex sergey