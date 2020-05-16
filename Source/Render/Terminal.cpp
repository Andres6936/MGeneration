// Design by Joan Andrés.

#include <BearLibTerminal/BearLibTerminal.hpp>

#include "Render/Terminal.hpp"

using namespace Gen;

Terminal::Terminal()
{
	TerminalOpen();
	TerminalSet("terminal: encoding=437");
	TerminalSet("window: size=80x25, cellsize=auto, title=MGeneration");
}

Terminal::~Terminal()
{
	TerminalClose();
}

void Terminal::clear()
{
	TerminalClear();
}

void Terminal::refresh()
{
	TerminalRefresh();
}

int Terminal::getKeyPressed()
{
	return TerminalRead();
}

void Terminal::setBackgroundColor(const char* name)
{
	TerminalColor(ColorFromName(name));
}

void Terminal::write(Renderer::UInt32 x, Renderer::UInt32 y, int code)
{
	TerminalPut(x, y, code);
}