/*++
/* NAME
/*	postfix 1
/* SUMMARY
/*	Postfix control program
/* SYNOPSIS
/* .fi
/*	\fBpostfix\fR [\fB-Dv\fR] [\fB-c \fIconfig_dir\fR] \fIcommand\fR
/* DESCRIPTION
/*	This command is reserved for the superuser. To submit mail,
/*	use the Postfix \fBsendmail\fR command.
/*
/*	The \fBpostfix\fR command controls the operation of the Postfix
/*	mail system: start or stop the \fBmaster\fR daemon, do a health
/*	check, and other maintenance.
/*
/*	The \fBpostfix\fR command sets up a standardized environment and
/*	runs the \fBpostfix-script\fR shell script to do the actual work.
/*
/*	The following commands are implemented:
/* .IP \fBcheck\fR
/*	Validate the Postfix mail system configuration. Warn about bad
/*	directory/file ownership or permissions, and create missing
/*	directories.
/* .IP \fBstart\fR
/*	Start the Postfix mail system. This also runs the configuration
/*	check described above.
/* .IP \fBstop\fR
/*	Stop the Postfix mail system in an orderly fashion. Running processes
/*	are allowed to terminate at their earliest convenience.
/* .sp
/*	Note: in order to refresh the Postfix mail system after a
/*	configuration change, do not use the \fBstart\fR and \fBstop\fR
/*	commands in succession. Use the \fBreload\fR command instead.
/* .IP \fBabort\fR
/*	Stop the Postfix mail system abruptly. Running processes are
/*	signaled to stop immediately.
/* .IP \fBflush\fR
/*	Force delivery: attempt to deliver every message in the deferred
/*	mail queue. Normally, attempts to deliver delayed mail happen at
/*	regular intervals, the interval doubling after each failed attempt.
/* .sp
/*	Warning: flushing undeliverable mail frequently will result in
/*	poor delivery performance of all other mail.
/* .IP \fBreload\fR
/*	Re-read configuration files. Running processes terminate at their
/*	earliest convenience.
/* .IP "\fBset-permissions\fR \fB[\fIname\fR=\fIvalue ...\fB]\fR
/*	Set the ownership and permissions of Postfix related files and 
/*	directories, as specified in the \fBpostfix-files\fR file.
/* .sp
/*	Specify \fIname\fR=\fIvalue\fR to override and update specific
/*	main.cf configuration parameters. Use this, for example, to
/*	change the \fBmail_owner\fR or \fBsetgid_group\fR setting for an
/*	already installed Postfix system.
/* .IP "\fBupgrade-configuration\fR \fB[\fIname\fR=\fIvalue ...\fB]\fR
/*	Update the \fBmain.cf\fR and \fBmaster.cf\fR files with information
/*	that Postfix needs in order to run: add or update services, and add
/*	or update configuration parameter settings.
/* .sp
/*	Specify \fIname\fR=\fIvalue\fR to override and update specific
/*	main.cf configuration parameters.
/* .PP
/*	The following options are implemented:
/* .IP "\fB-c \fIconfig_dir\fR"
/*	Read the \fBmain.cf\fR and \fBmaster.cf\fR configuration files in
/*	the named directory instead of the default configuration directory.
/*	Use this to distinguish between multiple Postfix instances on the
/*	same host.
/* .IP "\fB-D\fR (with \fBpostfix start\fR only)"
/*	Run each Postfix daemon under control of a debugger as specified
/*	via the \fBdebugger_command\fR configuration parameter.
/* .IP \fB-v\fR
/*	Enable verbose logging for debugging purposes. Multiple \fB-v\fR
/*	options make the software increasingly verbose.
/* ENVIRONMENT
/* .ad
/* .fi
/*	The \fBpostfix\fR command exports the following environment
/*	variables before executing the \fBpostfix-script\fR file:
/* .IP \fBMAIL_CONFIG\fR
/*	This is set when the -c command-line option is present.
/* .IP \fBMAIL_VERBOSE\fR
/*	This is set when the -v command-line option is present.
/* .IP \fBMAIL_DEBUG\fR
/*	This is set when the -D command-line option is present.
/* CONFIGURATION PARAMETERS
/* .ad
/* .fi
/*	The following \fBmain.cf\fR configuration parameters are
/*	exported as environment variables with the same names:
/* .IP "\fBcommand_directory (see 'postconf -d' output)\fR"
/*	The location of all postfix administrative commands.
/* .IP "\fBdaemon_directory (see 'postconf -d' output)\fR"
/*	The directory with Postfix support programs and daemon programs.
/* .IP "\fBconfig_directory (see 'postconf -d' output)\fR"
/*	The default location of the Postfix main.cf and master.cf
/*	configuration files.
/* .IP "\fBqueue_directory (see 'postconf -d' output)\fR"
/*	The location of the Postfix top-level queue directory.
/* .IP "\fBmail_owner (postfix)\fR"
/*	The UNIX system account that owns the Postfix queue and most Postfix
/*	daemon processes.
/* .IP "\fBsetgid_group (postdrop)\fR"
/*	The group ownership of set-gid Postfix commands and of group-writable
/*	Postfix directories.
/* .IP "\fBsendmail_path (see 'postconf -d' output)\fR"
/*	A Sendmail compatibility feature that specifies the location of
/*	the Postfix sendmail(1) command.
/* .IP "\fBnewaliases_path (see 'postconf -d' output)\fR"
/*	Sendmail compatibility feature that specifies the location of the
/*	newaliases(1) command.
/* .IP "\fBmailq_path (see 'postconf -d' output)\fR"
/*	Sendmail compatibility feature that specifies where the Postfix
/*	mailq(1) command is installed.
/* .IP "\fBhtml_directory (see 'postconf -d' output)\fR"
/*	The location of Postfix HTML files that describe how to build,
/*	configure or operate a specific Postfix subsystem or feature.
/* .IP "\fBmanpage_directory (see 'postconf -d' output)\fR"
/*	Where the Postfix manual pages are installed.
/* .IP "\fBreadme_directory (see 'postconf -d' output)\fR"
/*	The location of Postfix README files that describe how to build,
/*	configure or operate a specific Postfix subsystem or feature.
/* .PP
/*	Other configuration parameters:
/* .IP "\fBconfig_directory (see 'postconf -d' output)\fR"
/*	The default location of the Postfix main.cf and master.cf
/*	configuration files.
/* .IP "\fBimport_environment (see 'postconf -d' output)\fR"
/*	The list of environment parameters that a Postfix process will
/*	import from a non-Postfix parent process.
/* .IP "\fBsyslog_facility (mail)\fR"
/*	The syslog facility of Postfix logging.
/* .IP "\fBsyslog_name (postfix)\fR"
/*	The mail system name that is prepended to the process name in syslog
/*	records, so that "smtpd" becomes, for example, "postfix/smtpd".
/* FILES
/*	/etc/postfix/main.cf, Postfix configuration parameters
/*	/etc/postfix/master.cf, Postfix daemon processes
/*	/etc/postfix/postfix-files, file/directory permissions
/*	/etc/postfix/postfix-script, administrative commands
/*	/etc/postfix/post-install, post-installation configuration
/* SEE ALSO
/*	Commands:
/*	postalias(1), create/update/query alias database
/*	postcat(1), examine Postfix queue file
/*	postkick(1), trigger Postfix daemon
/*	postlock(1), Postfix-compatible locking
/*	postlog(1), Postfix-compatible logging
/*	postmap(1), Postfix lookup table manager
/*	postqueue(1), Postfix mail queue control
/*	postsuper(1), Postfix housekeeping
/*	sendmail(1), Sendmail compatibility interface
/*
/*	Postfix configuration:
/*	postconf(5), Postfix configuration parameters
/*
/*	Table-driven mechanisms:
/*	access(5), Postfix SMTP access control table
/*	aliases(5), Postfix alias database
/*	header_checks(5), body_checks(5), content inspection
/*	canonical(5), Postfix address rewriting
/*	relocated(5), Users that have moved
/*	transport(5), Postfix routing table
/*	virtual(5), Postfix virtual aliasing
/*
/*	Table lookup mechanisms:
/*	cidr_table(5), Associate CIDR pattern with value
/*	ldap_table(5), Postfix LDAP client
/*	mysql_table(5), Postfix MYSQL client
/*	pcre_table(5), Associate PCRE pattern with value
/*	pgsql_table(5), Postfix PostgreSQL client
/*	regexp_table(5), Associate POSIX regexp pattern with value
/*	tcp_table(5), Postfix client-server table lookup
/*
/*	Daemon processes:
/*	anvil(8), Postfix connection/rate limiting
/*	bounce(8), defer(8), trace(8), Delivery status reports
/*	cleanup(8), canonicalize and enqueue message
/*	error(8), Postfix error delivery agent
/*	flush(8), Postfix fast ETRN service
/*	lmtp(8), Postfix LMTP client
/*	local(8), Postfix local delivery agent
/*	master(8), Postfix master daemon
/*	oqmgr(8), old Postfix queue manager
/*	pickup(8), Postfix local mail pickup
/*	pipe(8), deliver mail to non-Postfix command
/*	proxymap(8), Postfix lookup table proxy server
/*	qmgr(8), Postfix queue manager
/*	qmqpd(8), Postfix QMQP server
/*	showq(8), list Postfix mail queue
/*	smtp(8), Postfix SMTP client
/*	smtpd(8), Postfix SMTP server
/*	spawn(8), run non-Postfix server
/*	trivial-rewrite(8), Postfix address rewriting
/*	verify(8), Postfix address verification
/*	virtual(8), Postfix virtual delivery agent
/*
/*	Other:
/*	syslogd(8), system logging
/* README FILES
/*	Use "\fBpostconf readme_directory\fR" or
/*	"\fBpostconf html_directory\fR to locate this information.
/*	OVERVIEW, overview of Postfix commands and processes
/*	BASIC_CONFIGURATION_README, Postfix basic configuration
/*	ADDRESS_REWRITING_README, Postfix address rewriting
/*	SMTPD_ACCESS_README, SMTP relay/access control
/*	CONTENT_FILTER_README, Postfix content inspection
/*	QSHAPE_README, Postfix queue analysis
/* LICENSE
/* .ad
/* .fi
/*	The Secure Mailer license must be distributed with this software.
/* AUTHOR(S)
/*	Wietse Venema
/*	IBM T.J. Watson Research
/*	P.O. Box 704
/*	Yorktown Heights, NY 10598, USA
/*--*/

/* System library. */

#include <sys_defs.h>
#include <sys/stat.h>
#include <vstream.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <syslog.h>
#ifdef USE_PATHS_H
#include <paths.h>
#endif

/* Utility library. */

#include <msg.h>
#include <msg_vstream.h>
#include <msg_syslog.h>
#include <stringops.h>
#include <clean_env.h>
#include <argv.h>
#include <safe.h>

/* Global library. */

#include <mail_conf.h>
#include <mail_params.h>

/* Additional installation parameters. */

static char *var_sendmail_path;
static char *var_mailq_path;
static char *var_newalias_path;
static char *var_manpage_dir;
static char *var_sample_dir;
static char *var_readme_dir;
static char *var_html_dir;

/* check_setenv - setenv() with extreme prejudice */

static void check_setenv(char *name, char *value)
{
#define CLOBBER 1
    if (setenv(name, value, CLOBBER) < 0)
	msg_fatal("setenv: %m");
}

/* main - run administrative script from controlled environment */

int     main(int argc, char **argv)
{
    char   *script;
    struct stat st;
    char   *slash;
    int     fd;
    int     ch;
    ARGV   *import_env;
    static CONFIG_STR_TABLE str_table[] = {
	VAR_SENDMAIL_PATH, DEF_SENDMAIL_PATH, &var_sendmail_path, 1, 0,
	VAR_MAILQ_PATH, DEF_MAILQ_PATH, &var_mailq_path, 1, 0,
	VAR_NEWALIAS_PATH, DEF_NEWALIAS_PATH, &var_newalias_path, 1, 0,
	VAR_MANPAGE_DIR, DEF_MANPAGE_DIR, &var_manpage_dir, 1, 0,
	VAR_SAMPLE_DIR, DEF_SAMPLE_DIR, &var_sample_dir, 1, 0,
	VAR_README_DIR, DEF_README_DIR, &var_readme_dir, 1, 0,
	VAR_HTML_DIR, DEF_HTML_DIR, &var_html_dir, 1, 0,
	0,
    };

    /*
     * Be consistent with file permissions.
     */
    umask(022);

    /*
     * To minimize confusion, make sure that the standard file descriptors
     * are open before opening anything else. XXX Work around for 44BSD where
     * fstat can return EBADF on an open file descriptor.
     */
    for (fd = 0; fd < 3; fd++)
	if (fstat(fd, &st) == -1
	    && (close(fd), open("/dev/null", O_RDWR, 0)) != fd)
	    msg_fatal("open /dev/null: %m");

    /*
     * Set up diagnostics. XXX What if stdin is the system console during
     * boot time? It seems a bad idea to log startup errors to the console.
     * This is UNIX, a system that can run without hand holding.
     */
    if ((slash = strrchr(argv[0], '/')) != 0 && slash[1])
	argv[0] = slash + 1;
    if (isatty(STDERR_FILENO))
	msg_vstream_init(argv[0], VSTREAM_ERR);
    msg_syslog_init(argv[0], LOG_PID, LOG_FACILITY);

    /*
     * The mail system must be run by the superuser so it can revoke
     * privileges for selected operations. That's right - it takes privileges
     * to toss privileges.
     */
    if (getuid() != 0) {
	msg_error("to submit mail, use the Postfix sendmail command");
	msg_fatal("the postfix command is reserved for the superuser");
    }
    if (unsafe() != 0)
	msg_fatal("the postfix command must not run as a set-uid process");

    /*
     * Parse switches.
     */
    while ((ch = GETOPT(argc, argv, "c:Dv")) > 0) {
	switch (ch) {
	default:
	    msg_fatal("usage: %s [-c config_dir] [-Dv] command", argv[0]);
	case 'c':
	    if (*optarg != '/')
		msg_fatal("-c requires absolute pathname");
	    check_setenv(CONF_ENV_PATH, optarg);
	    break;
	case 'D':
	    check_setenv(CONF_ENV_DEBUG, "");
	    break;
	case 'v':
	    msg_verbose++;
	    check_setenv(CONF_ENV_VERB, "");
	    break;
	}
    }

    /*
     * Copy a bunch of configuration parameters into the environment for easy
     * access by the maintenance shell script.
     */
    mail_conf_read();
    get_mail_conf_str_table(str_table);

    /*
     * Environment import filter, to enforce consistent behavior whether this
     * command is started by hand, or at system boot time. This is necessary
     * because some shell scripts use environment settings to override
     * main.cf settings.
     */
    import_env = argv_split(var_import_environ, ", \t\r\n");
    clean_env(import_env->argv);
    argv_free(import_env);

    check_setenv("PATH", ROOT_PATH);		/* sys_defs.h */
    check_setenv(CONF_ENV_PATH, var_config_dir);/* mail_conf.h */

    check_setenv(VAR_COMMAND_DIR, var_command_dir);	/* main.cf */
    check_setenv(VAR_DAEMON_DIR, var_daemon_dir);	/* main.cf */
    check_setenv(VAR_QUEUE_DIR, var_queue_dir);	/* main.cf */
    check_setenv(VAR_CONFIG_DIR, var_config_dir);	/* main.cf */

    /*
     * Do we want to keep adding things here as shell scripts evolve?
     */
    check_setenv(VAR_MAIL_OWNER, var_mail_owner);	/* main.cf */
    check_setenv(VAR_SGID_GROUP, var_sgid_group);	/* main.cf */
    check_setenv(VAR_SENDMAIL_PATH, var_sendmail_path);	/* main.cf */
    check_setenv(VAR_MAILQ_PATH, var_mailq_path);	/* main.cf */
    check_setenv(VAR_NEWALIAS_PATH, var_newalias_path);	/* main.cf */
    check_setenv(VAR_MANPAGE_DIR, var_manpage_dir);	/* main.cf */
    check_setenv(VAR_SAMPLE_DIR, var_sample_dir);	/* main.cf */
    check_setenv(VAR_README_DIR, var_readme_dir);	/* main.cf */
    check_setenv(VAR_HTML_DIR, var_html_dir);	/* main.cf */

    /*
     * Make sure these directories exist. Run the maintenance scripts with as
     * current directory the mail database.
     */
    if (chdir(var_command_dir))
	msg_fatal("chdir(%s): %m", var_command_dir);
    if (chdir(var_daemon_dir))
	msg_fatal("chdir(%s): %m", var_daemon_dir);
    if (chdir(var_queue_dir))
	msg_fatal("chdir(%s): %m", var_queue_dir);

    /*
     * Run the management script with as process name ourself.
     */
    script = concatenate(var_config_dir, "/postfix-script", (char *) 0);
    execvp(script, argv + optind - 1);
    msg_fatal("%s: %m", script);
}
