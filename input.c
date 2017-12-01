/* input.c: interface for input handlers

   Copyright (C) 1999, 2000, 2001 Bernhard Herzog.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License
   as published by the Free Software Foundation; either version 2.1 of
   the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA. */


#undef HAVE_MAGICK

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* Def: HAVE_CONFIG_H */

#include "autotrace.h"
#include "input.h"
#include "input-pnm.h"
#include "input-bmp.h"
#include "input-tga.h"
#include "xstd.h"
#include "filename.h"
#include "strgicmp.h"


struct input_format_entry {
  const char * name;
  const char * descr;
  at_input_read_func reader;
};

#define END   {NULL, NULL, NULL}

static struct input_format_entry input_formats[] = {
  { "TGA",   "Truevision Targa image",         input_tga_reader },
  { "PBM",   "Portable bitmap format",         input_pnm_reader },
  { "PNM",   "Portable anymap format",         input_pnm_reader },
  { "PGM",   "Portable graymap format",        input_pnm_reader },
  { "PPM",   "Portable pixmap format",         input_pnm_reader },
  { "BMP",   "Microsoft Windows bitmap image", input_bmp_reader },
  END
};

at_input_read_func
at_input_get_handler (at_string filename)
{
  char * ext = find_suffix (filename);
  if (ext == NULL)
     ext = "";

  return at_input_get_handler_by_suffix (ext);
}

at_input_read_func
at_input_get_handler_by_suffix (at_string suffix)
{
  struct input_format_entry * format;
  
  if (!suffix || suffix[0] == '\0')
    return NULL;

  for (format = input_formats ; format->name; format++)
    {
      if (strgicmp (suffix, format->name))
        {
          return format->reader;
        }
    }
  return NULL;
}

char **
at_input_list_new (void)
{
  char ** list;
  int count, count_int = 0;
  int i;


  struct input_format_entry * entry;
  for (entry = input_formats; entry->name; entry++)
    count_int++;
  count = count_int;

  XMALLOC(list, sizeof(char*)*((2*count)+1));

  entry = input_formats;
  for (i = 0; i < count_int; i++)
    {
      list[2*i] = (char *)entry[i].name;
      list[2*i+1] = (char *)entry[i].descr;
    }

  list[2*i] = NULL;
  return list;
}

void
at_input_list_free(char ** list)
{
  free(list);
}

char *
at_input_shortlist (void)
{
  char * list;
  int count_int = 0;
  size_t length = 0;
  int i;


  struct input_format_entry * entry;
  for (entry = input_formats; entry->name; entry++)
    {
      count_int++;
      length += strlen (entry->name) + 2;
  }


  XMALLOC(list, sizeof (char) * (length + 1 + 2));

  entry = input_formats;
  strcpy (list, (char *) entry[0].name);
  for (i = 1; i < count_int - 1; i++)
    {
      strcat (list, ", ");
      strcat (list, (char *) entry[i].name);
    }

  strcat (list, " or ");
  strcat (list, (char *) entry[i].name);
  return list;
}

int
at_input_add_handler (at_string suffix, 
		      at_string description,
		      at_input_read_func func)
{
  return 0;
}
