#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int paste_from_clipboard(char * buffer) {
    Display *dpy = XOpenDisplay(NULL);
    if (!dpy) {
        fprintf(stderr, "No X11 display found.\n");
        return 1;
    }
    *buffer=0;

    Window win = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, 1, 1, 0, 0, 0);
    Atom clipboard = XInternAtom(dpy, "CLIPBOARD", False);
    Atom utf8 = XInternAtom(dpy, "UTF8_STRING", False);

    XConvertSelection(dpy, clipboard, utf8, clipboard, win, CurrentTime);

    XEvent evt;
    int done = 0;
    while (!done) {
        XNextEvent(dpy, &evt);
        if (evt.type == SelectionNotify && evt.xselection.selection == clipboard) {
            if (evt.xselection.property) {
                Atom actual_type;
                int actual_format;
                unsigned long nitems, bytes_after;
                unsigned char *prop;
                XGetWindowProperty(dpy, win, clipboard, 0, (~0L), False, utf8,
                                   &actual_type, &actual_format, &nitems, &bytes_after, &prop);
                if (prop) {
		    strncpy(buffer,prop,65536);
                    XFree(prop);
                }
            }
            done = 1;
        }
    }
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
    return 0;
}

int main(int argc, char ** argv) {
  char buffer[65536];
  size_t size;
  paste_from_clipboard(buffer);
  size=strnlen(buffer,65536);
  fwrite(buffer,1,size,stdout);
  if (buffer[size-1]!='\n')
   fputs("\n",stdout);
  return 0;
}

