/* output.c: interface for output handlers

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

#include "output.h"
#include "xstd.h"
#include "filename.h"
#include "strgicmp.h"

#include "output-eps.h"
#include "output-er.h"
#include "output-p2e.h"
#include "output-sk.h"
#include "output-svg.h"
#include "output-fig.h"

#include "output-emf.h"
#include "output-mif.h"
#include "output-dxf.h"
#include "output-epd.h"
#include "output-pdf.h"
#include "output-cgm.h"
#include "output-dr2d.h"


struct output_format_entry {
    const char * name;
    const char * descr;
    at_output_write_func writer;
};

#define END   {NULL, NULL, NULL}
static struct output_format_entry output_formats[] = {
    {"eps",	"Encapsulated PostScript",	output_eps_writer},
    {"ai",	"Adobe Illustrator",		output_eps_writer},
    {"p2e",	"pstoedit frontend format",	output_p2e_writer},
    {"sk",	"Sketch",			output_sk_writer},
    {"svg",	"Scalable Vector Graphics",	output_svg_writer},
    {"fig",     "XFIG 3.2",                     output_fig_writer},
    {"emf",     "Enhanced Metafile format",     output_emf_writer},
    {"mif",     "FrameMaker MIF format",        output_mif_writer},
    {"er",      "Elastic Reality Shape file",   output_er_writer},
    {"dxf",     "DXF format (without splines)", output_dxf12_writer},
    {"epd",     "EPD format",                   output_epd_writer},
    {"pdf",     "PDF format",                   output_pdf_writer},
    {"cgm",     "Computer Graphics Metafile",   output_cgm_writer},
    {"dr2d",    "IFF DR2D format",              output_dr2d_writer},
    END
};


static at_bool streq (const char * a, const char * b);

at_output_write_func
at_output_get_handler(at_string filename)
{
  char * ext = find_suffix (filename);
  if (ext == NULL)
    ext = "";
  
  return at_output_get_handler_by_suffix (ext);
}

at_output_write_func
at_output_get_handler_by_suffix(at_string suffix)
{
  struct output_format_entry * format;

  if (!suffix || suffix[0] == '\0')
    return NULL;

  for (format = output_formats ; format->name; format++)
    {
      if (strgicmp (suffix, format->name))
        {
          return format->writer;
        }
    }
  return NULL;

}

char **
at_output_list_new (void)
{
  char ** list;
  int count_out = 0, count;
  int i;

  struct output_format_entry * entry;

  
  for (entry = output_formats; entry->name; entry++)
    count_out++;

  count = count_out;

  
  XMALLOC(list, sizeof(char*)*((2*count)+1));

  entry = output_formats;
  for (i = 0; i < count_out; i++)
    {
      list[2*i] = (char *)entry[i].name;
      list[2*i+1] = (char *)entry[i].descr;
    }

  list[2*i] = NULL;
  return list;
}

void
at_output_list_free(char ** list)
{
  free(list);
}

char *
at_output_shortlist (void)
{
  char * list;
  int count = 0;
  size_t length = 0;
  int i;

  struct output_format_entry * entry;

  for (entry = output_formats; entry->name; entry++)
    {
      count++;
      length += strlen (entry->name) + 2;
    }


  
  XMALLOC(list, sizeof (char) * (length + 1 + 2));

  entry = output_formats;
  strcpy (list, (char *) entry[0].name);
  for (i = 1; i < count - 1; i++)
    {
      strcat (list, ", ");
      strcat (list, (char *) entry[i].name);
    }

  strcat (list, " or ");
  strcat (list, (char *) entry[i].name);
  return list;
}

int
at_output_add_handler (at_string suffix, 
		       at_string description, 
		       at_output_write_func func)
{
  return 0;
}

void
at_spline_list_foreach (at_spline_list_type * list,
			AtSplineListForeachFunc func,
			at_address user_data)
{
  unsigned i;
  for (i = 0; i < AT_SPLINE_LIST_LENGTH(list); i++)
    {
      func (list, AT_SPLINE_LIST_ELT(list, i), i, user_data);
    }
}


void
at_spline_list_array_foreach (at_spline_list_array_type *list_array,
			      AtSplineListArrayForeachFunc func,
			      at_address user_data)
{
  unsigned i;
  for (i = 0; i < AT_SPLINE_LIST_ARRAY_LENGTH(list_array); i++)
    {
      func (list_array, AT_SPLINE_LIST_ARRAY_ELT(list_array, i), i, user_data);
    }
}

static at_bool
streq (const char * a, const char * b)
{
  if (!strcmp(a, b))
    return true;
  else
    return false;
}
