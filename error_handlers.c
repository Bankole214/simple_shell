#include "main.h"
/**
 * print_err - print not found error
 * @prc_path: process path
 * @count: command count
 * @err_message: error message
*/
void print_err(char *prc_path, size_t count, const char *err_message)
{
	_put_e(prc_path);
	_put_e(": ");
	print_digits_e(count);
	_put_e(": ");
	_puts_e(err_message);
	free(prc_path);
}
/**
 * print_err_nf - print command not found error
 * @prc_path: process path
 * @count: command count
 * @cmd: command
 * @err_message: error message
*/
void print_err_nf(char *prc_path, size_t count, char *cmd,
const char *err_message)
{
	_put_e(prc_path);
	_put_e(": ");
	print_digits_e(count);
	_put_e(": ");
	_put_e(cmd);
	_put_e(": ");
	_puts_e(err_message);
	free(prc_path);
}
/**
 * print_exit_err - print not found error
 * @prc_path: process path
 * @count: command count
 * @str: arg str
*/
void print_exit_err(char *prc_path, size_t count, const char *str)
{
	_put_e(prc_path);
	_put_e(": ");
	print_digits_e(count);
	_put_e(": ");
	_put_e("exit: Illegal number: ");
	_puts_e(str);
	free(prc_path);
}
/**
 * print_cd_err - print cd error
 * @prc_path: process path
 * @count: command count
 * @str: arg str
*/
void print_cd_err(char *prc_path, size_t count, const char *str)
{
	_put_e(prc_path);
	_put_e(": ");
	print_digits_e(count);
	_put_e(": ");
	_put_e("cd: cant cd to ");
	_puts_e(str);
	free(prc_path);
}
/**
 * print_err_sep - print not found error
 * @prc_path: process path
 * @count: command count
 * @sep: seperator
*/
void print_err_sep(char *prc_path, size_t count, char *sep)
{
	_put_e(prc_path);
	_put_e(": ");
	print_digits_e(count);
	_put_e(": ");
	_put_e("Syntax error: ");
	_put_e("\"");
	_put_e(sep);
	_put_e("\"");
	_puts_e(" unexpected");
	free(prc_path);
}
