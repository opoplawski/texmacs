
/******************************************************************************
* MODULE     : tm_window.hpp
* DESCRIPTION: TeXmacs main data structures (buffers, views and windows)
* COPYRIGHT  : (C) 1999  Joris van der Hoeven
*******************************************************************************
* This software falls under the GNU general public license and comes WITHOUT
* ANY WARRANTY WHATSOEVER. See the file $TEXMACS_PATH/LICENSE for more details.
* If you don't have this file, write to the Free Software Foundation, Inc.,
* 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
******************************************************************************/

#ifndef TM_WINDOW_H
#define TM_WINDOW_H
#include "tm_buffer.hpp"

window texmacs_window (wk_widget wid, tree geom);
window texmacs_window (widget wid, tree geom);

class tm_window_rep {
public:
  window    win;
  tm_widget wid;
  int       id;

public:
  hashmap<tree,tree> props;
  int                serial;
  int                sfactor;       // the shrinking factor

public:
  object*  texmacs_menu;       // accelerate menu rendering
  object*  texmacs_icon_menu;  // accelerate icon bar rendering

public:
  tm_window_rep (tm_widget wid2, tree geom);
  ~tm_window_rep ();

  inline void set_property (scheme_tree what, scheme_tree val) {
    props (what)= val; }
  inline scheme_tree get_property (scheme_tree what) {
    return props [what]; }

  void set_window_name (string s);

  inline wk_widget get_main () {
    return wk_widget (wid); }
  inline wk_widget get_header () {
    return get_main () ["header"]; }
  inline wk_widget get_canvas () {
    return get_main () ["canvas"]; }
  inline wk_widget get_footer () {
    return get_main () ["footer"]; }

  inline void interactive (string name, string type, array<string> def,
			   string& s, command cmd) {
    wid->interactive (name, type, def, s, cmd); }
  inline void interactive_return () {
    wid->interactive_return (); }
  void set_left_footer (string s);
  void set_right_footer (string s);
  int  get_footer_mode ();
  void set_footer_mode (int which);
  bool get_footer_flag ();
  void set_footer_flag (bool on);
  int  get_shrinking_factor ();
  void set_shrinking_factor (int sf);

  void menu_main (string menu);
  void menu_icons (int which, string menu);
};

class tm_view_rep {
public:
  tm_buffer buf;
  editor    ed;
  tm_window win;
  inline tm_view_rep (tm_buffer buf2, editor ed2):
    buf (buf2), ed (ed2), win (NULL) {}
};

typedef tm_buffer_rep* tm_buffer;
typedef tm_view_rep*   tm_view;
typedef tm_window_rep* tm_window;

#endif // defined TM_WINDOW_H
