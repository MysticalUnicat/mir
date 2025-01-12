/* This file is a part of MIR project.
   Copyright (C) 2020-2024 Vladimir Makarov <vmakarov.gcc@gmail.com>.
*/

#ifndef C2MIR_H

#define C2MIR_H

#include "mir.h"

#define COMMAND_LINE_SOURCE_NAME "<command-line>"
#define STDIN_SOURCE_NAME "<stdin>"

struct c2mir_macro_command {
  int def_p;              /* #define or #undef */
  const char *name, *def; /* def is used only when def_p is true */
};

struct c2m_output {
  FILE *file;
  void (*callback)(void * user_data, const char * text, size_t length);
  void * callback_user_data;
};

typedef struct c2m_output *c2m_output_t;

struct c2mir_options {
  c2m_output_t message_output;
  int debug_p, verbose_p, ignore_warnings_p, no_prepro_p, prepro_only_p;
  int syntax_only_p, pedantic_p, asm_p, object_p;
  size_t module_num;
  c2m_output_t prepro_output;
  const char *output_file_name;
  size_t macro_commands_num, include_dirs_num;
  struct c2mir_macro_command *macro_commands;
  const char **include_dirs;
  size_t string_headers_num;
  const char **string_headers_name;
  const char **string_headers_content;
};

void c2mir_init (MIR_context_t ctx);
void c2mir_finish (MIR_context_t ctx);
int c2mir_compile (MIR_context_t ctx, struct c2mir_options *ops, int (*getc_func) (void *),
                   void *getc_data, const char *source_name, c2m_output_t output);

#endif
