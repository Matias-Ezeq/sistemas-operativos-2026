class PCB(pid, tiempoEjecucion) :
    estado = "Creado"
    self.pid = pid
    self.tiempoEjecucion = tiempoEjecucion

    def setEstado(nuevoEstado):
        self.estado = nuevoEstado

    def ejecutar():
        if (self.estado == "Preparado" and self.tiempoEjecucion > 0 ) :
            self.estado
            self.tiempoEjecucion -= 1

        if (self.tiempoEjecucion == 0) :
            self.estado = "Finalizado"
        else :
            self.estado = ""