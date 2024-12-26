PROJECT_NAME = cobra

# Diretórios
SRC_DIR = src
BUILD_DIR = build
ENTITIES_DIR = $(SRC_DIR)/entitites
COMPONENTS_DIR = $(SRC_DIR)/components

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/components/*.cpp) $(wildcard $(SRC_DIR)/entitites/*.cpp) $(wildcard Dependencies/ImGUI/*.cpp)

# Diretórios de inclusão
INCLUDE_DIRS = -IDependencies/SDL2/include -Iinclude -Isrc/entitites -IDependencies/ImGUI/include/ImGUI -IDependencies/SDL2/include/SDL2

# Diretórios de bibliotecas
LIB_DIRS = -LDependencies/SDL2/x64

# Bibliotecas
LIBS = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lmingw32

# Nome do executável
EXECUTABLE = $(BUILD_DIR)/$(PROJECT_NAME).exe
DEBUG_EXECUTABLE = $(BUILD_DIR)/$(PROJECT_NAME)_debug.exe

# Flags de compilação
CXXFLAGS = $(INCLUDE_DIRS) $(LIB_DIRS) $(LIBS)

# Alvo padrão
default: $(EXECUTABLE)

# Alvo de debug
debug: CXXFLAGS += -g
debug: $(DEBUG_EXECUTABLE)

# Regra para criar o executável padrão
$(EXECUTABLE): $(SRC_FILES)
	g++ $(SRC_FILES) -o $(EXECUTABLE) $(CXXFLAGS)

# Regra para criar o executável de debug
$(DEBUG_EXECUTABLE): $(SRC_FILES)
	g++ $(SRC_FILES) -o $(DEBUG_EXECUTABLE) $(CXXFLAGS)

# Alvo de limpeza
clean:
	rm -rf $(BUILD_DIR)/*.exe
	rm -rf $(BUILD_DIR)/*.o
