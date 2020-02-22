ifdef ComSpec
    RM=del /F /Q
    COPY=copy
else
    RM=rm -rf
    COPY=cp
endif

all: tem 

tem: tem.tpl 
	@admb -f tem.tpl 


clean:
	@$(RM) tem.cpp
	@$(RM) tem.htp
	@$(RM) tem.obj

