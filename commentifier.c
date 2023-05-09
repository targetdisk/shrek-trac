#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(CODIFIER)
  #define BEGIN_LOOKIE   "{{\n"
  #define PUT_BEGINNING  { printf("```\n"); }
  #define PUT_ENDING     { printf("```\n"); }
#elif defined(DOS_CODIFIER)
  #define BEGIN_LOOKIE   "{{\r\n"
  #define PUT_BEGINNING  { printf("```\n"); }
  #define PUT_ENDING     { printf("```\n"); }
#elif defined(INLINE_CODIFIER)
  #define BEGIN_LOOKIE   "{{"
  #define PUT_BEGINNING  { putchar('`'); }
  #define PUT_ENDING     { putchar('`'); }
#else
  #define BEGIN_LOOKIE   "{{#!comment"
  #define PUT_BEGINNING  { printf("<!--"); }
  #define PUT_ENDING     { printf("-->"); }
#endif /* CODIFIER */

char *look_for(const char *term, size_t depth) {
  if (*term == '\0') {
    return NULL;
  }
  char *ret = NULL;
  int c = '\0';
  for (;;) {
    c = getchar();
    if (c == *term) {
      ret = look_for(++term, ++depth);
      if (ret)
        *(--ret) = c;
      return ret;
    } else {
      goto ret;
    }
  }
ret:
  ret = malloc(sizeof(char) * (depth + 1));
  if (ret) {
    ret += depth;
    *ret = '\0';
    *(--ret) = c;
  } else {
    fprintf(stderr, "ERROR: malloc failed on string data!!\n");
    exit(ENOMEM);
  }
  return ret;
}

void inner(void) {
  for (int c = '\0';;) {
    c = getchar();
    switch (c) {
      case EOF:
        exit(0);
      case '}':
        char *lookie_str = look_for("}}", 1);
        if (lookie_str == NULL) {
          PUT_ENDING;
          return;
        } else {
          printf("%c%s", c, lookie_str);
        }
        break;
      default:
        putchar(c);
        break;
    }
  }
}

int main(void) {
  for (int c = '\0';;) {
    c = getchar();
    switch (c) {
      case EOF:
        return 0;
      case '{':
        char *lookie_str = look_for(BEGIN_LOOKIE, 1);
        if (lookie_str == NULL) {
          PUT_BEGINNING;
          inner();
        } else {
          printf("%c%s", c, lookie_str);
        }
        break;
      default:
        putchar(c);
        break;
    }
  }
}
