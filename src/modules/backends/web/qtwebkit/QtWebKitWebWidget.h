#ifndef OTTER_QTWEBKITWEBWIDGET_H
#define OTTER_QTWEBKITWEBWIDGET_H

#include "../../../../ui/WebWidget.h"

#include <QtWebKitWidgets/QWebHitTestResult>
#include <QtWebKitWidgets/QWebInspector>
#include <QtWebKitWidgets/QWebPage>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QSplitter>

namespace Otter
{

class NetworkAccessManager;
class QtWebKitWebPage;

class QtWebKitWebWidget : public WebWidget
{
	Q_OBJECT

public:
	explicit QtWebKitWebWidget(bool privateWindow = false, QWidget *parent = NULL, QtWebKitWebPage *page = NULL);

	void print(QPrinter *printer);
	WebWidget* clone(QWidget *parent = NULL);
	QAction* getAction(WindowAction action);
	QUndoStack* getUndoStack();
	QString getDefaultTextEncoding() const;
	QString getTitle() const;
	QVariant evaluateJavaScript(const QString &script);
	QUrl getUrl() const;
	QIcon getIcon() const;
	QPixmap getThumbnail();
	HistoryInformation getHistory() const;
	int getZoom() const;
	bool isLoading() const;
	bool isPrivate() const;
	bool find(const QString &text, FindFlags flags = HighlightAllFind);
	bool eventFilter(QObject *object, QEvent *event);

public slots:
	void triggerAction(WindowAction action, bool checked = false);
	void setDefaultTextEncoding(const QString &encoding);
	void setHistory(const HistoryInformation &history);
	void setZoom(int zoom);
	void setUrl(const QUrl &url);

protected:
	QWebPage::WebAction mapAction(WindowAction action) const;

protected slots:
	void triggerAction();
	void loadStarted();
	void loadFinished(bool ok);
	void downloadFile(const QNetworkRequest &request);
	void downloadFile(QNetworkReply *reply);
	void linkHovered(const QString &link, const QString &title);
	void saveState(QWebFrame *frame, QWebHistoryItem *item);
	void restoreState(QWebFrame *frame);
	void notifyTitleChanged();
	void notifyUrlChanged(const QUrl &url);
	void notifyIconChanged();
	void showContextMenu(const QPoint &position);

private:
	QWebView *m_webView;
	QWebInspector *m_inspector;
	NetworkAccessManager *m_networkAccessManager;
	QSplitter *m_splitter;
	QPixmap m_thumbnail;
	QWebHitTestResult m_hitResult;
	QHash<WindowAction, QAction*> m_actions;
	bool m_isLinkHovered;
	bool m_isLoading;
};

}

#endif
