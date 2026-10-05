#include <crypt.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define DB_DBM_HSEARCH 1
#include <db.h>

char *readStr() {
	size_t n = 0;
	char *result = NULL;

	ssize_t chars = getline(&result, &n, stdin);

	result[chars-1] = '\0';

	return result;
}

int main() {
	DBM *dbf;

	if ((dbf = dbm_open("imapusers", O_RDWR, 0644)) == NULL) {
		perror("Failed to open database");
		return errno;
	}

	for (;;) {
		datum key, val;

		printf("Username? ");
		char *uname = readStr();
		if (*uname == '\0')
			break;

		printf("Password? ");
		char *pass = readStr();

		struct crypt_data cd = { 0 };
		char *salt = crypt_gensalt(NULL, 0, NULL, 0);
		if (salt == NULL) {
			perror("Failed to generate salt");
			break;
		}
		char *hash = crypt_r(pass, salt, &cd);
		if (hash == NULL) {
			perror("Failed to hash password");
			break;
		}

		key.dptr = uname;
		key.dsize = strlen(uname);
		val.dptr = hash;
		val.dsize = strlen(hash);

		dbm_store(dbf, key, val, DBM_REPLACE);
		free(uname);
		free(pass);

	}

	dbm_close(dbf);
	return 0;
}
