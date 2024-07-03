#include <ctype.h>
#include <stdio.h>
#include <string.h>

typedef enum {
  ENCODE,
  DECODE
} CaesarMode;

#define ERROR_MSG "\x1b[0;31m[ERROR] \x1b[0m"

#define ENCODE_SHORT "-e"
#define DECODE_SHORT "-d"

#define SHIFT 3

void show_usage(const char* prog_name) {
  printf("usage: %s [mode] <text>\n", prog_name);
  printf(ENCODE_SHORT " : encode\n");
  printf(DECODE_SHORT " : decode\n");
}
void process_text(char* txt, CaesarMode mode) {
  int txt_len = strlen(txt);
  char buf[txt_len];
  int offset = mode == ENCODE ? SHIFT:-SHIFT;
  for (int i = 0; i < txt_len; i++) {
    int is_uppercase = txt[i] >= 'A' && txt[i] <= 'Z';
    
    if (isalpha(txt[i]) == 0) { 
      buf[i] = txt[i];
      continue;
    }

    switch (mode) {
      case ENCODE:
        if (is_uppercase && txt[i] >= 'Z' + 1 - SHIFT) {
          buf[i] = 'A' + (txt[i] - ('Z' + 1 - SHIFT));    
          continue;
        } else if (!is_uppercase && txt[i] >= 'z' + 1 - SHIFT) {
          buf[i] = 'a' + (txt[i] - ('z' + 1 - SHIFT));
          continue;
        }
        break;
      case DECODE:
        if (is_uppercase && txt[i] <= 'A' + SHIFT - 1) {
          buf[i] = 'Z' - (('A' + SHIFT - 1) % txt[i]);
          continue;
        } else if (!is_uppercase && txt[i] <= 'a' + SHIFT - 1) {
          buf[i] = 'z' - (('a' + SHIFT - 1) % txt[i]);
          continue;
        }
        break;
    }

    buf[i] = txt[i] + offset;
  }
  buf[txt_len] = '\0';
  printf("%s\n", buf);
}
int main(int argc, char* argv[]) {
  CaesarMode mode;
  if (argc < 3) {
    fprintf(stderr, ERROR_MSG "insufficient arguments\n");
    show_usage(argv[0]);
    return 1;
  }
  if (strcmp(argv[1], ENCODE_SHORT) == 0) {
    mode = ENCODE;
  } else if (strcmp(argv[1], DECODE_SHORT) == 0) {
    mode = DECODE;
  } else {
    fprintf(stderr, ERROR_MSG "unknown option\n");
    show_usage(argv[0]);
    return 1;
  }
  process_text(argv[2], mode);
  return 0;
}
