

set( HEADERS
  pagingmodel.h
  pagingmodel_p.h
  qtrestclient_helpertypes.h
  requestbuilder_p.h
  restclass_p.h
  restclient_p.h
  restreply_p.h
  qtrestclient_global.h
  ipaging.h
  requestbuilder.h
  restclass.h
  restclient.h
  restreply.h
  standardpaging_p.h
  restreplyawaitable.h
  restreplyawaitable_p.h
  )

# !no_json_serializer {
# 	HEADERS += \
# 		metacomponent.h \
# 		paging_fwd.h \
# 		paging.h \
# 		genericrestreply.h \
# 		simple.h
# }


FILE(COPY ${HEADERS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../QtRestClient)

add_custom_target(QtRestClient_copy_headers  ALL COMMENT "Copying header files"  )

set( HEADERS_COPIED )
foreach(filepath ${HEADERS})
  get_filename_component(filename ${filepath} NAME)
  add_custom_command(TARGET QtRestClient_copy_headers COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/${filepath} ${CMAKE_CURRENT_BINARY_DIR}/../QtRestClient/${filename} )
  list(APPEND HEADERS_COPIED ${CMAKE_CURRENT_SOURCE_DIR}/${filepath} )
endforeach()
  
set(CMAKE_AUTOMOC 1)

#QT5_WRAP_CPP(qtWrapCpp_MOC_SRCS_QtRestClient ${HEADERS_COPIED} TARGET QtRestClient )


set( SOURCES 
  pagingmodel.cpp
  requestbuilder.cpp
  restclass.cpp
  restclient.cpp
  restreply.cpp
  standardpaging.cpp
  ipaging.cpp
  restreplyawaitable.cpp
 # ${qtWrapCpp_MOC_SRCS_QtRestClient}
  )


add_library(QtRestClient  ${SOURCES})
add_library(Qt5::RestClient ALIAS QtRestClient )

add_dependencies(QtRestClient QtRestClient_copy_headers)

target_link_libraries(QtRestClient
  PRIVATE
  Qt5::Core Qt5::CorePrivate
  Qt5::Network
)

target_include_directories(QtRestClient
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/..> #headers
#  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}> #moc
)

target_compile_definitions( QtRestClient PUBLIC Q_RESTCLIENT_NO_JSON_SERIALIZER )

set_property(TARGET QtRestClient PROPERTY CXX_STANDARD 17)

include(GNUInstallDirs)
install(TARGETS QtRestClient
  EXPORT QtRestClientTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

