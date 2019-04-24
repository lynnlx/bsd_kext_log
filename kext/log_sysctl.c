/*
 * Created 190423 lynnl
 */

#include <sys/sysctl.h>

#include "log_sysctl.h"
#include "log_kctl.h"
#include "utils.h"

static SYSCTL_NODE(
    /* No parent */,
    OID_AUTO,
    kextlog,
    CTLFLAG_RD | CTLFLAG_LOCKED,
    NULL,
    "(unused) root sysctl node: kextlog"
)

static SYSCTL_NODE(
    _kextlog,
    OID_AUTO,
    statistics,
    CTLFLAG_RD | CTLFLAG_LOCKED,
    NULL,
    "(unused) sysctl node: kextlog.statistics"
)

struct kextlog_statistics log_stat = {};

static SYSCTL_QUAD(
    _kextlog_statistics,
    OID_AUTO,
    syslog,
    CTLFLAG_RD | CTLFLAG_LOCKED,
    (uint64_t *) &log_stat.syslog,
    "(unused) sysctl nub: kextlog.statistics.syslog"
)

static SYSCTL_QUAD(
    _kextlog_statistics,
    OID_AUTO,
    heapmsg,
    CTLFLAG_RD | CTLFLAG_LOCKED,
    (uint64_t *) &log_stat.heapmsg,
    "(unused) sysctl nub: kextlog.statistics.heapmsg"
)

static SYSCTL_QUAD(
    _kextlog_statistics,
    OID_AUTO,
    stackmsg,
    CTLFLAG_RD | CTLFLAG_LOCKED,
    (uint64_t *) &log_stat.stackmsg,
    "(unused) sysctl nub: kextlog.statistics.stackmsg"
)

static SYSCTL_QUAD(
    _kextlog_statistics,
    OID_AUTO,
    toctou,
    CTLFLAG_RD | CTLFLAG_LOCKED,
    (uint64_t *) &log_stat.toctou,
    "(unused) sysctl nub: kextlog.statistics.toctou"
)

static SYSCTL_QUAD(
    _kextlog_statistics,
    OID_AUTO,
    oom,
    CTLFLAG_RD | CTLFLAG_LOCKED,
    (uint64_t *) &log_stat.oom,
    "(unused) sysctl nub: kextlog.statistics.oom"
)

static SYSCTL_QUAD(
    _kextlog_statistics,
    OID_AUTO,
    enqueue_failure,
    CTLFLAG_RD | CTLFLAG_LOCKED,
    (uint64_t *) &log_stat.enqueue_failure,
    "(unused) sysctl nub: kextlog.statistics.enqueue_failure"
)

static struct sysctl_oid * const sysctl_entries[] = {
    &sysctl__kextlog_statistics_syslog,
    &sysctl__kextlog_statistics_heapmsg,
    &sysctl__kextlog_statistics_stackmsg,
    &sysctl__kextlog_statistics_toctou,
    &sysctl__kextlog_statistics_oom,
    &sysctl__kextlog_statistics_enqueue_failure,
};

void log_sysctl_register(void)
{
    size_t i;
    for (i = 0; i < ARRAY_SIZE(sysctl_entries); i++) {
        sysctl_register_oid(sysctl_entries[i]);
    }
}

void log_sysctl_deregister(void)
{
    size_t i;
    for (i = 0; i < ARRAY_SIZE(sysctl_entries); i++) {
        sysctl_unregister_oid(sysctl_entries[i]);
    }
}
