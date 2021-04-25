#ifndef QTRESTCLIENT_IPAGING_H
#define QTRESTCLIENT_IPAGING_H

#include "QtRestClient/qtrestclient_global.h"

#include <variant>

#include <QtCore/qjsonarray.h>
#include <QtCore/qjsonvalue.h>
#include <QtCore/qcborvalue.h>
#include <QtCore/qcborarray.h>
#include <QtCore/qurl.h>
#include <QtCore/qvariant.h>

#ifndef Q_RESTCLIENT_NO_JSON_SERIALIZER
namespace QtJsonSerializer {
class SerializerBase;
}
#endif

namespace QtRestClient {

//! Interface to parse generic paging objects and operate on them
class Q_RESTCLIENT_EXPORT IPaging
{
	Q_DISABLE_COPY(IPaging)
public:
	IPaging();
	virtual ~IPaging();

	//! Returns the items of this paging object, i.e. it's data
	virtual std::variant<QCborArray, QJsonArray> items() const = 0;

	//! Returns the total number of objects there are
	virtual qint64 total() const;
	//! Returns the offset this paging begins at
	virtual qint64 offset() const;
	//! Returns true, if there is a next paging object
	virtual bool hasNext() const = 0;
	//! Returns the link to the next paging object
	virtual QUrl next() const = 0;
	//! Returns true, if there is a previous paging object
	virtual bool hasPrevious() const;
	//! Returns the link to the previous paging object
	virtual QUrl previous() const;
	//! Returns a hash containing all properties of the original JSON
	virtual QVariantMap properties() const = 0;
	//! Returns the original JSON element parsed
	virtual std::variant<QCborValue, QJsonValue> originalData() const = 0;
};

//! Interface to parse generic CBOR paging objects and operate on them
class Q_RESTCLIENT_EXPORT ICborPaging : public IPaging
{
public:
	//! @copybrief IPaging::items
	virtual QCborArray cborItems() const = 0;
	//! @copybrief IPaging::originalData
	virtual QCborValue originalCbor() const = 0;

	std::variant<QCborArray, QJsonArray> items() const final;
	std::variant<QCborValue, QJsonValue> originalData() const final;
};

//! Interface to parse generic JSON paging objects and operate on them
class Q_RESTCLIENT_EXPORT IJsonPaging : public IPaging
{
public:
	//! @copybrief IPaging::items
	virtual QJsonArray jsonItems() const = 0;
	//! @copybrief IPaging::originalData
	virtual QJsonValue originalJson() const = 0;

	std::variant<QCborArray, QJsonArray> items() const final;
	std::variant<QCborValue, QJsonValue> originalData() const final;
};

//! A factory interface to create IPaging instances from raw data
class Q_RESTCLIENT_EXPORT IPagingFactory
{
	Q_DISABLE_COPY(IPagingFactory)

public:
	IPagingFactory();
	virtual ~IPagingFactory();

	//! Creates a new paging object of the given data
#ifndef Q_RESTCLIENT_NO_JSON_SERIALIZER
	virtual IPaging *createPaging(QtJsonSerializer::SerializerBase *serializer, const std::variant<QCborValue, QJsonValue> &data) const = 0;
#else
	virtual IPaging *createPaging(const std::variant<QCborValue, QJsonValue> &data) const = 0;
#endif
};

}

Q_DECLARE_METATYPE(QtRestClient::IPaging*)

#endif // QTRESTCLIENT_IPAGING_H
