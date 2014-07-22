TBLIB=${TBLIB_ROOT}/include
INCLUDE=-I ${TBLIB}/tbnet -I ${TBLIB}/tbsys
LIB=-L ${TBLIB_ROOT}/lib
default:server client
	echo "done"
server:
	g++ -g calserver.cpp ${INCLUDE} ${LIB} -ltbnet -ltbsys
client:
	g++ -o calClient -g calclient.cpp ${INCLUDE} ${LIB} -ltbnet -ltbsys
