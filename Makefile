INCLUDE_DIR = C:/Users/trung/OneDrive/Documents/Learn_Makefile/include
SOURCE_DIR  = C:/Users/trung/OneDrive/Documents/Learn_Makefile/source
OUTPUT_DIR  = C:/Users/trung/OneDrive/Documents/Learn_Makefile/output


SOURCE_FILES_DIRS := $(foreach SOURCE_DIR,$(SOURCE_DIR),$(wildcard $(SOURCE_DIR)/*.c))
SOURCE_FILES := $(notdir $(SOURCE_FILES_DIRS))

OUTPUT_FILES_DIRS := $(foreach OUTPUT_DIR,$(OUTPUT_DIR),$(wildcard $(OUTPUT_DIR)/*.o))
OBJ_FILES := $(subst .c,.o,$(SOURCE_FILES))

INCLUDE_FILES_DIRS :=  $(foreach INCLUDE_DIR,$(INCLUDE_DIR),$(wildcard $(INCLUDE_DIR)/*.h))

vpath %.c $(SOURCE_DIR)
vpath $.h $(INCLUDE_DIR)

HexDisplay.exe: $(OBJ_FILES) 
	@gcc $(OUTPUT_FILES_DIRS) -o $(OUTPUT_DIR)/HexDisplay.exe
	@$(OUTPUT_DIR)/$@
%.o: %.c $(INCLUDE_FILES_DIRS)
	@gcc -c $< -I $(INCLUDE_DIR) -o $(OUTPUT_DIR)/$@
clear:
	rm $(OUTPUT_DIR)/*

# echo = printf in C #
# @ clear "echo" command in result #
# $(PRO_DIR) is value, PRO_DIR is name of variable #
# function $(subst ee, EE, feet on the street) = fEEt on the strEEt # 
# $@ is target printf-% #

print:
	@echo $(PRO_DIR)
printf-%: #all of printf_everything is OK#
	@echo $($(subst printf-,,$@))
