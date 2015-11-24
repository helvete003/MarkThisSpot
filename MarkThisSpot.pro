APP_NAME = MarkThisSpot

CONFIG += qt warn_on cascades10

include(config.pri)
LIBS += -lbbsystem
LIBS += -lbbdata
LIBS += -lQtLocationSubset
LIBS += -lbbplatform