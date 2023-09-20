#' Convert HMDB Metabolites to a SQLite database.
#'
#' Create an SQLite compound database
#'
#' @param sqlite.file Path to the SQLite file to create.
#' @return Nothing.
#' @examples
#' # Copy all HMDB entries into a new SQLite database:
#' biodbHmdb::hmdbToSqlite('myfile.sqlite')
#' @export
hmdbToSqlite <- function(sqlite.file='hmdb.sqlite') {

    # Open HMDB connector
    bdb <- biodb::newInst()
    hmdb <- bdb$getFactory()$createConn('hmdb.metabolites')

    # Create SQLite database
    hmdbSqlite <- bdb$getFactory()$createConn('comp.sqlite', url=sqlite.file)
    hmdbSqlite$allowEditing()
    hmdbSqlite$allowWriting()

    # Copy entries
    ids <- hmdb$getEntryIds(max.results=0)
    sqlite_ids <- hmdbSqlite$getEntryIds(max.results=0)
    ids <- ids[ ! ids %in% sqlite_ids]
    prg <- biodb::Progress$new(biodb=bdb, msg='Copying entries.',
        total=length(ids))
    N <- 10000
    i <- 0
    for (id in ids) {

        # Clone entry
        clone <- hmdb$getEntry(id)$cloneInstance(hmdbSqlite$getDbClass())

        # Add new entry
        hmdbSqlite$addNewEntry(clone)

        # Write
        i <- i + 1
        if (i %% N == 0) {

            # Write into SQLite file
            hmdbSqlite$write()

            # Delete all entries in memory in order to minimize memory usage
            hmdb$deleteAllEntriesFromVolatileCache()
            hmdbSqlite$deleteAllEntriesFromVolatileCache()
        }

        # Progress message
        prg$increment()
    }

    # Write into SQLite file
    hmdbSqlite$write()

    return(invisible(NULL))
}
