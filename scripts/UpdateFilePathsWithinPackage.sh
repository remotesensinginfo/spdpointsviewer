#
# use otool -L to list libraries which are linked.
#
#
#






# Change paths on libgsl:
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./libgsl.0.dylib

# Change paths on libhdf5_cpp.7.dylib:
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./libhdf5_cpp.7.dylib

# Change paths on libhdf5.7.dylib:
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./libhdf5.7.dylib


# Change paths on libgdal:
install_name_tool -change /usr/local//lib/libhdf5.6.dylib @executable_path/../Frameworks/libhdf5.6.dylib ./libgdal.1.dylib

# Change path on libgeotiff
install_name_tool -change /usr/local/lib/libproj.0.dylib @executable_path/../Frameworks/libproj.0.dylib ./libgeotiff.2.0.0.dylib
install_name_tool -change /usr/local/lib/libtiff.3.dylib @executable_path/../Frameworks/libtiff.3.dylib ./libgeotiff.2.0.0.dylib

# Change paths on liblas
install_name_tool -change /usr/local/lib/libtiff.3.dylib @executable_path/../Frameworks/libtiff.3.dylib ./liblas.2.0.0.dylib
install_name_tool -change /usr/local/lib/libgeotiff.2.dylib @executable_path/../Frameworks/libgeotiff.2.dylib ./liblas.2.0.0.dylib
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./liblas.2.0.0.dylib
install_name_tool -change /usr/local/lib/liblaszip.2.0.1.dylib @executable_path/../Frameworks/liblaszip.2.0.1.dylib ./liblas.2.0.0.dylib
install_name_tool -change libboost_program_options.dylib @executable_path/../Frameworks/libboost_program_options.dylib liblas.2.0.0.dylib
install_name_tool -change libboost_thread.dylib @executable_path/../Frameworks/libboost_thread.dylib liblas.2.0.0.dylib
install_name_tool -change libboost_program_options.dylib @executable_path/../Frameworks/libboost_program_options.dylib ./liblas.2.0.0.dylib 
install_name_tool -change libboost_thread.dylib @executable_path/../Frameworks/libboost_thread.dylib ./liblas.2.0.0.dylib 

# Change paths on liblas-c
install_name_tool -change libboost_program_options.dylib @executable_path/../Frameworks/libboost_program_options.dylib liblas_c.2.0.0.dylib 
install_name_tool -change libboost_thread.dylib @executable_path/../Frameworks/libboost_thread.dylib liblas_c.2.0.0.dylib 


install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./liblas_c.2.0.0.dylib
install_name_tool -change /usr/local/lib/libtiff.3.dylib @executable_path/../Frameworks/libtiff.3.dylib ./liblas_c.2.0.0.dylib
install_name_tool -change /usr/local/lib/libgeotiff.2.dylib @executable_path/../Frameworks/libgeotiff.2.0.0.dylib ./liblas_c.2.0.0.dylib
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./liblas_c.2.0.0.dylib
install_name_tool -change /usr/local/lib/liblaszip.2.0.1.dylib @executable_path/../Frameworks/liblaszip.2.0.1.dylib ./liblas_c.2.0.0.dylib
install_name_tool -change /usr/local/lib/libboost_program_options.dylib @executable_path/../Frameworks/libboost_program_options.dylib ./liblas.2.0.0.dylib
install_name_tool -change /usr/local/lib/libboost_thread.dylib @executable_path/../Frameworks/libboost_thread.dylib ./liblas.2.0.0.dylib
install_name_tool -change libboost_program_options.dylib @executable_path/../Frameworks/libboost_program_options.dylib ./liblas_c.2.0.0.dylib 
install_name_tool -change libboost_thread.dylib @executable_path/../Frameworks/libboost_thread.dylib ./liblas_c.2.0.0.dylib 

# Change paths on libspd
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./libspd.1.0.0.dylib
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./libspd.1.0.0.dylib
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./libspd.1.0.0.dylib
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./libspd.1.0.0.dylib
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./libspd.1.0.0.dylib
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./libspd.1.0.0.dylib
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./libspd.1.0.0.dylib
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./libspd.1.0.0.dylib
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./libspd.1.0.0.dylib
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.0.0.dylib ./libspd.1.0.0.dylib 


install_name_tool -change @executable_path/../Frameworks/libhdf5_hl.6.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./libspd.1.0.0.dylib
install_name_tool -change @executable_path/../Frameworks/libhdf5_cpp.6.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./libspd.1.0.0.dylib

#Change paths on libCGAL
install_name_tool -change libboost_thread.dylib @executable_path/../Frameworks/libboost_thread.dylib ./libCGAL.7.0.0.dylib 

# Change paths libqwt
#install_name_tool -change QtGui.framework/Versions/4/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/4/QtGui ./libqwt.5.2.1.dylib 
#install_name_tool -change QtCore.framework/Versions/4/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/4/QtCore ./libqwt.5.2.1.dylib 

# Change paths spd tools:

install_name_tool -change @executable_path/../Frameworks/libqwt.5.dylib @executable_path/../Frameworks/libqwt.5.2.1.dylib ./SPDPointsViewer 


#spd2spd
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spd2spd
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spd2spd
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spd2spd
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spd2spd
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spd2spd
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spd2spd
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spd2spd
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spd2spd
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spd2spd
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spd2spd
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spd2spd

#spdclearclass
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spdclearclass
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spdclearclass
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spdclearclass
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spdclearclass
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spdclearclass
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spdclearclass
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spdclearclass
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spdclearclass
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spdclearclass
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spdclearclass
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spdclearclass

#spdconwave
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spdconwave
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spdconwave
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spdconwave
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spdconwave
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spdconwave
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spdconwave
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spdconwave
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spdconwave
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spdconwave
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spdconwave
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spdconwave

#spddecomp
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spddecomp
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spddecomp
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spddecomp
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spddecomp
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spddecomp
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spddecomp
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spddecomp
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spddecomp
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spddecomp
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spddecomp
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spddecomp

#spddefheight
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spddefheight
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spddefheight
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spddefheight
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spddefheight
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spddefheight
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spddefheight
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spddefheight
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spddefheight
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spddefheight
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spddefheight
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spddefheight

#spddefrgb
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spddefrgb
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spddefrgb
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spddefrgb
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spddefrgb
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spddefrgb
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spddefrgb
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spddefrgb
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spddefrgb
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spddefrgb
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spddefrgb
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spddefrgb

#spdelevation
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spdelevation
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spdelevation
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spdelevation
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spdelevation
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spdelevation
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spdelevation
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spdelevation
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spdelevation
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spdelevation
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spdelevation
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spdelevation

#spdgrdclass
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spdgrdclass
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spdgrdclass
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spdgrdclass
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spdgrdclass
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spdgrdclass
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spdgrdclass
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spdgrdclass
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spdgrdclass
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spdgrdclass
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spdgrdclass
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spdgrdclass

#spdgrderrors
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spdgrderrors
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spdgrderrors
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spdgrderrors
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spdgrderrors
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spdgrderrors
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spdgrderrors
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spdgrderrors
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spdgrderrors
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spdgrderrors
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spdgrderrors
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spdgrderrors

#spdinfo
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spdinfo
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spdinfo
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spdinfo
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spdinfo
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spdinfo
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spdinfo
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spdinfo
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spdinfo
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spdinfo
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spdinfo
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spdinfo

#spdinterp
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spdinterp
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spdinterp
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spdinterp
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spdinterp
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spdinterp
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spdinterp
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spdinterp
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spdinterp
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spdinterp
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spdinterp
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spdinterp

#spdlastest
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spdlastest
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spdlastest
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spdlastest
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spdlastest
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spdlastest
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spdlastest
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spdlastest
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spdlastest
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spdlastest
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spdlastest
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spdlastest

#spdmccgrd
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spdmccgrd
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spdmccgrd
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spdmccgrd
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spdmccgrd
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spdmccgrd
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spdmccgrd
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spdmccgrd
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spdmccgrd
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spdmccgrd
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spdmccgrd
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spdmccgrd

#spdmerge
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spdmerge
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spdmerge
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spdmerge
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spdmerge
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spdmerge
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spdmerge
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spdmerge
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spdmerge
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spdmerge
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spdmerge
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spdmerge

#spdmetrics
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spdmetrics
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spdmetrics
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spdmetrics
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spdmetrics
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spdmetrics
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spdmetrics
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spdmetrics
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spdmetrics
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spdmetrics
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spdmetrics
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spdmetrics

#spdplanegrd
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spdplanegrd
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spdplanegrd
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spdplanegrd
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spdplanegrd
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spdplanegrd
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spdplanegrd
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spdplanegrd
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spdplanegrd
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spdplanegrd
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spdplanegrd
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spdplanegrd

#spdpmfgrd
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spdpmfgrd
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spdpmfgrd
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spdpmfgrd
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spdpmfgrd
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spdpmfgrd
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spdpmfgrd
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spdpmfgrd
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spdpmfgrd
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spdpmfgrd
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spdpmfgrd
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spdpmfgrd

#spdpolygrd
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spdpolygrd
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spdpolygrd
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spdpolygrd
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spdpolygrd
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spdpolygrd
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spdpolygrd
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spdpolygrd
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spdpolygrd
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spdpolygrd
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spdpolygrd
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spdpolygrd

#spdproj
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spdproj
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spdproj
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spdproj
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spdproj
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spdproj
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spdproj
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spdproj
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spdproj
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spdproj
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spdproj
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spdproj

#spdrmnoise
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spdrmnoise
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spdrmnoise
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spdrmnoise
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spdrmnoise
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spdrmnoise
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spdrmnoise
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spdrmnoise
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spdrmnoise
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spdrmnoise
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spdrmnoise
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spdrmnoise

#spdstats
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spdstats
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spdstats
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spdstats
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spdstats
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spdstats
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spdstats
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spdstats
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spdstats
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spdstats
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spdstats
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spdstats

#spdsubset
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spdsubset
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spdsubset
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spdsubset
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spdsubset
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spdsubset
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spdsubset
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spdsubset
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spdsubset
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spdsubset
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spdsubset
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spdsubset

#spdvecstats
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./spdvecstats
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./spdvecstats
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./spdvecstats
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./spdvecstats
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./spdvecstats
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./spdvecstats
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./spdvecstats
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./spdvecstats
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./spdvecstats
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./spdvecstats
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./spdvecstats

#updsubset
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./updsubset
install_name_tool -change /usr/local/lib/liblas.2.0.0.dylib @executable_path/../Frameworks/liblas.2.0.0.dylib ./updsubset
install_name_tool -change /usr/local/lib/liblas_c.2.0.0.dylib @executable_path/../Frameworks/liblas_c.2.0.0.dylib ./updsubset
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./updsubset
install_name_tool -change /usr/local/lib/libhdf5.7.dylib @executable_path/../Frameworks/libhdf5.7.dylib ./updsubset
install_name_tool -change /usr/local/lib/libhdf5_hl.7.dylib @executable_path/../Frameworks/libhdf5_hl.7.dylib ./updsubset
install_name_tool -change /usr/local/lib/libhdf5_cpp.7.dylib @executable_path/../Frameworks/libhdf5_cpp.7.dylib ./updsubset
install_name_tool -change /usr/local/lib/libxerces-c-3.1.dylib @executable_path/../Frameworks/libxerces-c-3.1.dylib ./updsubset
install_name_tool -change /usr/local/lib/libgsl.0.dylib @executable_path/../Frameworks/libgsl.0.dylib ./updsubset
install_name_tool -change /usr/local/lib/libgslcblas.0.dylib @executable_path/../Frameworks/libgslcblas.0.dylib ./updsubset
install_name_tool -change libCGAL.7.dylib @executable_path/../Frameworks/libCGAL.7.dylib ./updsubset


#SPDPointsViewer
install_name_tool -change QtGui.framework/Versions/4/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/4/QtGui ./SPDPointsViewer
install_name_tool -change QtCore.framework/Versions/4/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/4/QtCore ./SPDPointsViewer
install_name_tool -change QtOpenGL.framework/Versions/4/QtOpenGL @executable_path/../Frameworks/QtOpenGL.framework/Versions/4/QtOpenGL ./SPDPointsViewer
install_name_tool -change libspd.1.0.0.dylib @executable_path/../Frameworks/libspd.1.0.0.dylib ./SPDPointsViewer
install_name_tool -change /usr/local/lib/libgdal.1.dylib @executable_path/../Frameworks/libgdal.1.dylib ./SPDPointsViewer

