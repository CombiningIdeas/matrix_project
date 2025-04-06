# Компилятор:
CC = gcc

# Флаг cUnit:
LDFLAGS = -lcunit

#Фалги компиляции:
CFLAGS = -Wall -Wextra -g -std=c11 -DDEBUG

# Объектные файлы(.о-файлы)
OBJ_MAIN = src/matrix/matrix.o src/output/output.o src/main.o
OBJ_TEST = src/matrix/matrix.o src/output/output.o src/main.o tests/test_runner.o tests/tests_main.o tests/tests_matrix.o tests/tests_output.o 


# Имена для финальных исполняемых файлов
TARGET = build/package/matrix_main
TEST_TARGET = build/tests/matrix_tests


# Компиляция  main-исполняемого файла:
$(TARGET): $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJ_MAIN) -o $(TARGET)

# Компиляция tests-исполняемого файла:
$(TEST_TARGET): $(OBJ_TEST)
	$(CC) $(CFLAGS) $(OBJ_TEST) $(LDFLAGS) -o $(TEST_TARGET) 



# Правила компиляции каждого .c-файла в .o-файл
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@



# Очистка
clean:
	rm -f $(OBJ_MAIN) $(OBJ_TEST)

all-clean:
	rm -f $(OBJ_MAIN) $(OBJ_TEST) $(TARGET) $(TEST_TARGET)

# Перекомпиляция
rebuild: 
	clean $(TARGET) $(TEST_TARGET)