#!/bin/bash

echo "[*] Iniciando laboratorio de procesos..."

# =========================
# 1. Procesos con nombres engañosos
# =========================
echo "[+] Creando procesos con nombres sospechosos..."

bash -c 'exec -a systmd sleep 300' &
bash -c 'exec -a sshD sleep 300' &
bash -c 'exec -a cron_fake sleep 300' &

# =========================
# 2. Proceso con alto consumo de CPU
# =========================
echo "[+] Creando proceso con alto consumo de CPU..."

bash -c 'exec -a kworker_fake yes > /dev/null' &

# =========================
# 3. Creación de proceso zombie
# =========================
echo "[+] Generando proceso zombie..."

bash -c '
    ( 
        exit 0
    ) &
    sleep 300
' &

# =========================
# 4. Proceso normal (control)
# =========================
sleep 300 &

echo "[*] Listo. Analizar con:"
echo "    ps -eaf"
echo "    ps aux | grep Z"
echo "    top"
echo "    pstree -p"
