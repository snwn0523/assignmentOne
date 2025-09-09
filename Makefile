CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -g
TARGET  = a1

.PHONY: all clean testall test1 test2 test3 test4 test5 test6 test7

all: $(TARGET)

$(TARGET): main.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

testall: test1 test2 test3 test4 test5 test6 test7

test1: $(TARGET)
	./$(TARGET) inputs/testcase_1.txt > output1.txt
	diff -u output1.txt expected/output_1.txt

test2: $(TARGET)
	./$(TARGET) inputs/testcase_2.txt > output2.txt
	diff -u output2.txt expected/output_2.txt

test3: $(TARGET)
	./$(TARGET) inputs/testcase_3.txt > output3.txt
	diff -u output3.txt expected/output_3.txt

test4: $(TARGET)
	./$(TARGET) inputs/testcase_4.txt > output4.txt
	diff -u output4.txt expected/output_4.txt

test5: $(TARGET)
	./$(TARGET) inputs/testcase_5.txt > output5.txt
	diff -u output5.txt expected/output_5.txt

test6: $(TARGET)
	./$(TARGET) inputs/testcase_6.txt > output6.txt
	diff -u output6.txt expected/output_6.txt

test7: $(TARGET)
	./$(TARGET) inputs/testcase_7.txt > output7.txt
	diff -u output7.txt expected/output_7.txt

clean:
	rm -f $(TARGET) *.o output*.txt