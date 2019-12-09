#ifndef QTRESTCLIENT_RESTREPLY_P_H
#define QTRESTCLIENT_RESTREPLY_P_H

#include "restreply.h"

#include <QtCore/QPointer>
#include <QtCore/QRunnable>

#include <QtCore/private/qobject_p.h>

namespace QtRestClient {

class Q_RESTCLIENT_EXPORT RestReplyPrivate : public QObjectPrivate, public QRunnable
{
	Q_DECLARE_PUBLIC(RestReply)
public:
	using DataType = RestReply::DataType;
	using Error = RestReply::Error;

	static const QByteArray PropertyBuffer;

	static QNetworkReply *compatSend(QNetworkAccessManager *nam, const QNetworkRequest &request, const QByteArray &verb, const QByteArray &body);

	QPointer<QNetworkReply> networkReply;
	bool autoDelete = true;
	bool allowEmptyReplies = false;
#ifdef QT_RESTCLIENT_USE_ASYNC
	QThreadPool *asyncPool = nullptr;
#endif
	std::chrono::milliseconds retryDelay {-1};

	RestReplyPrivate();

	void connectReply();

	void _q_replyFinished();
	void _q_retryReply();
#ifndef QT_NO_SSL
	void _q_handleSslErrors(const QList<QSslError> &errors);
#endif

	void run() override;
};

Q_DECLARE_LOGGING_CATEGORY(logReply)

}

#endif // QTRESTCLIENT_RESTREPLY_P_H
