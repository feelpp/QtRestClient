#ifndef RESTREPLYAWAITABLE_P_H
#define RESTREPLYAWAITABLE_P_H

#include "restreplyawaitable.h"
#include <QtCore/QPointer>

namespace QtRestClient {

class RestReplyAwaitablePrivate
{
public:
	QPointer<RestReply> reply;

	RestReply::DataType successResult = std::nullopt;
	QScopedPointer<AwaitedException> errorResult;

	RestReplyAwaitablePrivate(RestReply *reply);
};

}

#endif // RESTREPLYAWAITABLE_P_H
