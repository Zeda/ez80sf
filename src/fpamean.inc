__fpamean:
  call __fpadd
  push hl
  ld hl,$800000
  add hl,bc
  adc a,a
  jr z,.return_0
  inc a
  jr z,.return_InfNaN
  dec a
  dec a
  rra
  push hl
  pop bc
  pop hl
  ret
.return_0:
  rra
  pop hl
  ret
.return_InfNaN:
  dec a
  rra
  pop hl
  ret
