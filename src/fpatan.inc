__fpatan:
;return x/bg(1,sqrt(1+x*x))
;Save UHL, UDE
  push hl,de

;Save input
  push bc,af

  push bc
  pop hl
  ld e,a
  call __fpmul

  ld hl,$800000
  ld e,$3F
  call __fpadd

  call __fpsqrt

  push bc
  ex (sp),hl
  pop bc
  ld e,a
  ld a,$3F
  call __fpibg

  pop de,hl
  ld e,d
  call __fpmul
  pop de,hl
  ret
