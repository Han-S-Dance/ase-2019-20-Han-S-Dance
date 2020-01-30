TARGET=ViscoelasticFluid

QT+=gui opengl core

isEqual(QT_MAJOR_VERSION, 5) {
        cache()
        DEFINES +=QT5BUILD
}

CONFIG-=app_bundle
CONFIG += console
CONFIG += c++14

INCLUDEPATH +=./include

HEADERS+= $$PWD/include/*.h

SOURCES+= $$PWD/src/*.cpp

LIBS+= -L/usr/local/lib -lgtest -lgtest_main -pthread

DESTDIR=./
OBJECTS_DIR=obj
MOC_DIR=moc

FORMS+= $$PWD/ui/MainWindow.ui
OTHER_FILES+= README.md


!equals(PWD, $${OUT_PWD}){
        copydata.commands = echo "creating destination dirs" ;

        copydata.commands += mkdir -p $$OUT_PWD/shaders ;
        copydata.commands += echo "copying files" ;

        copydata.commands += $(COPY_DIR) $$PWD/shaders/* $$OUT_PWD/shaders/ ;

        first.depends = $(first) copydata
        export(first.depends)
        export(copydata.commands)

        QMAKE_EXTRA_TARGETS += first copydata
}
NGLPATH=$$(NGLDIR)
isEmpty(NGLPATH){
        message("including $HOME/NGL")
        include($(HOME)/NGL/UseNGL.pri)
         win32:include($(HOMEDRIVE)\$(HOMEPATH)\NGL\UseNGL.pri)

}
else{
        message("Using custom NGL location")
        include($(NGLDIR)/UseNGL.pri)
}


