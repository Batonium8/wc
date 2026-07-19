#include <ctype.h>
#include <stdio.h>

struct word_count {
  long lines;
  long words;
  long bytes;
};
// @note Создаем структуру со счетчиками вне функции
// для обработки нескольких файлов без потери счетчиков из прошлых
static int wc_stream(FILE *stream, struct word_count *counters) {
  int ch;

  // Флаг для проверки внутри ли слова находится символ
  int in_word = 0;

  while ((ch = fgetc(stream)) != EOF) {
    counters->bytes++;
    if (ch == '\n') {
      counters->lines++;
    }
    if (!(in_word) && !isspace(ch)) {
      counters->words++;
      in_word = 1;
    } else if (isspace(ch)) {
      in_word = 0;
    }
  }
  if (ferror(stream)) {
    perror("Error while reading stream");
    return -1;
  }

  return 0;
}

static int wc_file(const char *filename, struct word_count *file_counter) {
  FILE *file = fopen(filename, "r");

  int result;

  if (file == NULL) {
    perror("Error while opening file");
    return -1;
  }

  result = wc_stream(file, file_counter);

  fclose(file);

  return result;
}

void print_counts(const char *label, const struct word_count *counters) {
  printf("%7ld %7ld %7ld %s\n", counters->lines, counters->words,
         counters->bytes, label);
}

int main(int argc, char *argv[]) { return 0; }
