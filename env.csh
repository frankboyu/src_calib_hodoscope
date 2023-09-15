# GlueX environment in C shell

source /group/halld/Software/build_scripts/gluex_env_boot_jlab.csh
gxenv $HALLD_VERSIONS/version.xml

setenv CCDB_USER boyu
setenv JANA_CALIB_URL "mysql://ccdb_user@hallddb.jlab.org/ccdb"
setenv CCDB_CONNECTION "mysql://ccdb_user@hallddb.jlab.org/ccdb"
