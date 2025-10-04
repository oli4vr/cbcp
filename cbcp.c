/* cbcp.c
 * by oli4vr
 *
 * Copy from stdin to the X11 clipboard
 */
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int copy_to_clipboard(const char *str) {
    Display *dpy = XOpenDisplay(NULL);
    if (!dpy) {
        fprintf(stderr, "No X11 display found.\n");
        return 1;
    }
    XCloseDisplay(dpy); // Just checking availability

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 2;
    }
    if (pid > 0) {
        // Parent exits
        return 0;
    }

    // Child process: do the clipboard work
    dpy = XOpenDisplay(NULL);
    if (!dpy) {
        fprintf(stderr, "No X11 display found (child).\n");
        exit(1);
    }

    Window win = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, 1, 1, 0, 0, 0);
    Atom clipboard = XInternAtom(dpy, "CLIPBOARD", False);
    Atom utf8 = XInternAtom(dpy, "UTF8_STRING", False);
    Atom targets = XInternAtom(dpy, "TARGETS", False);

    XSetSelectionOwner(dpy, clipboard, win, CurrentTime);
    if (XGetSelectionOwner(dpy, clipboard) != win) {
        fprintf(stderr, "Failed to set clipboard owner.\n");
        XDestroyWindow(dpy, win);
        XCloseDisplay(dpy);
        exit(2);
    }

    XEvent evt;
    int running = 1;
    while (running) {
        XNextEvent(dpy, &evt);
        if (evt.type == SelectionRequest) {
            XSelectionRequestEvent *req = &evt.xselectionrequest;
            XEvent respond;
            memset(&respond, 0, sizeof(respond));
            respond.xselection.type = SelectionNotify;
            respond.xselection.display = req->display;
            respond.xselection.requestor = req->requestor;
            respond.xselection.selection = req->selection;
            respond.xselection.time = req->time;
            respond.xselection.target = req->target;
            respond.xselection.property = None;

            if (req->target == targets) {
                Atom types[2] = {utf8, XA_STRING};
                XChangeProperty(dpy, req->requestor, req->property, XA_ATOM, 32,
                                PropModeReplace, (unsigned char *)types, 2);
                respond.xselection.property = req->property;
            } else if (req->target == utf8 || req->target == XA_STRING) {
                XChangeProperty(dpy, req->requestor, req->property, req->target, 8,
                                PropModeReplace, (unsigned char *)str, strlen(str));
                respond.xselection.property = req->property;
            }
            XSendEvent(dpy, req->requestor, 0, 0, &respond);
            XFlush(dpy);
        } else if (evt.type == SelectionClear) {
            running = 0;
        }
    }

    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
    exit(0);
}

int main(int argc, char ** argv) {
 size_t size;
 unsigned char buffer[65536];
 *buffer=0;
 size=fread(buffer,1,65536,stdin);
 buffer[65535]=0;

 return copy_to_clipboard(buffer);
}

