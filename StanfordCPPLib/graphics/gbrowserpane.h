/*
 * File: gbrowserpane.h
 * --------------------
 *
 * @version 2018/08/23
 * - renamed to gbrowserpane.h to replace Java version
 * @version 2018/07/15
 * - initial version
 */

#ifndef _gbrowserpane_h
#define _gbrowserpane_h

#include <string>
#include <QSize>
#include <QTextBrowser>
#include <QWidget>
#include "ginteractor.h"

class _Internal_QTextBrowser;

/*
 *
 */
class GBrowserPane : public GInteractor {
public:
    /*
     * Constructs a new browser pane.
     * If a URL string is passed, loads the data from that URL.
     * Otherwise, the pane is initially blank.
     */
    GBrowserPane(const std::string& url = "", QWidget* parent = nullptr);
    virtual ~GBrowserPane();

    /*
     * Returns the MIME content type for the current page.
     * The default content type is "text/html".
     * (If you need to look up the content type for a given file/page extension,
     * consider using the HttpServer::getContentType(extension) function.)
     */
    virtual std::string getContentType() const;

    virtual _Internal_QWidget* getInternalWidget() const;

    /*
     * Returns the URL of the web page or file name being currently viewed.
     * If no page or file has been loaded, returns an empty string.
     */
    virtual std::string getPageUrl() const;

    /*
     * Returns the full text of the current page or file being displayed in the pane.
     * This could be a fairly long string, depending on the page.
     * Initially an empty string if no page or file has yet been loaded.
     */
    virtual std::string getText() const;

    virtual std::string getType() const Q_DECL_OVERRIDE;
    virtual QWidget* getWidget() const Q_DECL_OVERRIDE;

    /*
     * Reads text from the given file and displays the entire file's text as the
     * contents of this formatted pane.
     * The pane will try to display the content in the best appropriate format,
     * such as rendering basic HTML content with formatting intact.
     * If the file does not exist or cannot be read, sets the pane's text to be empty.
     */
    virtual void readTextFromFile(std::istream& file);
    virtual void readTextFromFile(const std::string& filename);

    /*
     * Reads text from the given web page URL and displays the entire page's
     * text as the contents of this formatted pane.
     * If the page does not exist or cannot be read, sets the pane's text to be empty.
     */
    virtual void readTextFromUrl(const std::string& url);

    /*
     * Sets the MIME content type being used to display the current/future pages.
     * The default content type is "text/html".
     * The suggested use of this function would be to call it just before calling
     * loadTextFromFile or loadTextFromUrl.
     * (If you need to look up the content type for a given file/page extension,
     * consider using the HttpServer::getContentType(extension) function.)
     */
    virtual void setContentType(const std::string& contentType);

    /*
     * Sets the pane to display to the given contents using its current content type.
     * For example, if you build your own string of HTML or text content and want
     * to display it in the pane without saving it to a file, this is the method to use.
     */
    virtual void setText(const std::string& text);

private:
    Q_DISABLE_COPY(GBrowserPane)

    std::string _pageUrl;   // url/filename of the most recently loaded page

private:
    _Internal_QTextBrowser* _iqtextbrowser;

    friend class _Internal_QTextBrowser;
};

// Internal class; not to be used by clients.
/*
 * @private
 */
class _Internal_QTextBrowser : public QTextBrowser, public _Internal_QWidget {
    Q_OBJECT

public:
    _Internal_QTextBrowser(GBrowserPane* gbrowserpane, QWidget* parent = nullptr);
    virtual QSize sizeHint() const Q_DECL_OVERRIDE;

private:
    GBrowserPane* _gbrowserpane;
};

#include "private/init.h"   // ensure that Stanford C++ lib is initialized

#endif // _gbrowserpane_h