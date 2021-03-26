TEMPLATE = lib
CONFIG += staticlib
CONFIG += warning_clean exceptions examples_need_tools tests_need_tools c++17
DEFINES += QT_DEPRECATED_WARNINGS QT_ASCII_CAST_WARNINGS

DEFINES += Q_RESTCLIENT_NO_JSON_SERIALIZER

TARGET = ibat_gui_QtRestClient

QT = core network core-private
#MODULE_CONFIG += qrestbuilder
INCLUDEPATH += ../
#!no_json_serializer {
#	!qtHaveModule(jsonserializer): warning("Unable to find QtJsonSerializer module. To build without it, add \"CONFIG+=no_json_serializer\" to your qmake command line")
#	QT += jsonserializer
#} else {
#	MODULE_DEFINES += Q_RESTCLIENT_NO_JSON_SERIALIZER
#	DEFINES += Q_RESTCLIENT_NO_JSON_SERIALIZER
#}

HEADERS += \
	pagingmodel.h \
	pagingmodel_p.h \
	qtrestclient_helpertypes.h \
	requestbuilder_p.h \
	restclass_p.h \
	restclient_p.h \
	restreply_p.h \
	qtrestclient_global.h \
	ipaging.h \
	requestbuilder.h \
	restclass.h \
	restclient.h \
	restreply.h \
	standardpaging_p.h \
	restreplyawaitable.h \
	restreplyawaitable_p.h

#!no_json_serializer {
#	HEADERS += \
#		metacomponent.h \
#		paging_fwd.h \
#		paging.h \
#		genericrestreply.h \
#		simple.h
#}

SOURCES += \
	pagingmodel.cpp \
	requestbuilder.cpp \
	restclass.cpp \
	restclient.cpp \
	restreply.cpp \
	standardpaging.cpp \
	ipaging.cpp \
	restreplyawaitable.cpp
