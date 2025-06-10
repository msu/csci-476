FROM handsonsecurity/seed-server:apache-php

ARG WWWDir=/var/www/sql_injection

COPY code $WWWDir
COPY sql_injection.conf  /etc/apache2/sites-available
RUN  a2ensite sql_injection.conf 



