# Simple Makefile for sorting benchmarks
# Usage:
#   make            (builds binary)
#   make run        (runs binary)
#   make clean      (removes build artifacts)

CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Wpedantic

OBJDIR := build
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRC))
DEPS := $(patsubst %.o,%.d,$(OBJ))

TARGET := sort_bench

# exe extension for Windows
EXEEXT :=
ifeq ($(OS),Windows_NT)
EXEEXT := .exe
endif
OUT := $(TARGET)$(EXEEXT)

.PHONY: all clean run rebuild

# default target
all: $(OUT)

# link
$(OUT): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# compile into build/ and generate dependency files
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -MMD -MP -MF $(patsubst %.o,%.d,$@)

# ensure build dir exists
$(OBJDIR):
ifeq ($(OS),Windows_NT)
	@powershell -NoProfile -Command "if (-not (Test-Path -LiteralPath '$(OBJDIR)')) { New-Item -ItemType Directory -Path '$(OBJDIR)' | Out-Null }"
else
	@mkdir -p $(OBJDIR)
endif

# include dependencies
-include $(DEPS)

# --- run: check up-to-date ---
ifeq ($(OS),Windows_NT)
run:
	@powershell -NoProfile -Command "$$out = '$(OUT)'; if (-not (Test-Path -LiteralPath $$out)) { Write-Host 'Executable ''$$out'' is missing. Please run: make clean && make all'; exit 1 }; $$exe = Get-Item -LiteralPath $$out; $$changed = Get-ChildItem -File -Recurse -Include *.cpp,*.c,*.h,*.hpp -ErrorAction SilentlyContinue | Where-Object { $$_.LastWriteTime -gt $$exe.LastWriteTime }; if ($$changed) { Write-Host 'Executable ''$$out'' is outdated. Please run: make clean && make all'; exit 1 }; Write-Host 'Executable up-to-date. Running .\$$out'; & .\$$out; exit $$LASTEXITCODE"
else
run:
	@sh -c '\
	OUT="$(OUT)"; \
	if [ ! -f "$$OUT" ]; then \
	  echo "Executable '\''$$OUT'\'' is missing. Please run: make clean && make all"; exit 1; \
	fi; \
	if find . \( -name "*.cpp" -o -name "*.c" -o -name "*.h" -o -name "*.hpp" \) -newer "$$OUT" -print -quit | grep -q .; then \
	  echo "Executable '\''$$OUT'\'' is outdated. Please run: make clean && make all"; exit 1; \
	fi; \
	echo "Executable up-to-date. Running ./$$OUT"; ./$$OUT'
endif

# --- clean with safety checks ---
ifeq ($(OS),Windows_NT)
clean:
	@powershell -NoProfile -Command "$$dir = '$(OBJDIR)'; if ([string]::IsNullOrEmpty($$dir)) { Write-Error 'Refusing: OBJDIR empty'; exit 1 }; $$resolved = Resolve-Path -LiteralPath $$dir -ErrorAction SilentlyContinue; if ($$resolved) { $$p = $$resolved.Path; $$root = [System.IO.Path]::GetPathRoot($$p); if ($$p -eq $$root) { Write-Error 'Refusing to remove root'; exit 1 }; if ($$p -eq (Get-Location).Path) { Write-Error 'Refusing to remove current directory'; exit 1 }; Remove-Item -LiteralPath $$p -Recurse -Force -ErrorAction SilentlyContinue; Write-Host 'Removed: ' + $$p }; if (Test-Path -LiteralPath '$(OUT)') { Remove-Item -LiteralPath '$(OUT)' -Force -ErrorAction SilentlyContinue; Write-Host 'Removed: $(OUT)' }"
else
clean:
	@sh -c '\
	if [ -z "$(OBJDIR)" ]; then echo "Refusing: OBJDIR empty"; exit 1; fi; \
	abspath=$$(realpath -m "$(OBJDIR)" 2>/dev/null || echo "$(OBJDIR)"); \
	case "$$abspath" in \
		/) echo "Refusing to remove root /"; exit 1 ;; \
		.) echo "Refusing to remove current directory ."; exit 1 ;; \
	esac; \
	if [ -d "$$abspath" ]; then rm -rf -- "$$abspath"; echo "Removed: $$abspath"; else echo "Nothing to remove: $(OBJDIR)"; fi; \
	if [ -f "$(OUT)" ]; then rm -f -- "$(OUT)"; echo "Removed: $(OUT)"; fi'
endif

# optional rebuild target
rebuild: clean all
