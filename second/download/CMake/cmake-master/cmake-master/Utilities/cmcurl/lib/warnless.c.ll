; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/warnless.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define zeroext i16 @curlx_ultous(i64 %ulnum) #0 !dbg !19 {
entry:
  %ulnum.addr = alloca i64, align 8
  store i64 %ulnum, i64* %ulnum.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %ulnum.addr, metadata !73, metadata !74), !dbg !75
  br label %do.body, !dbg !76

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !77

do.end:                                           ; preds = %do.body
  %0 = load i64, i64* %ulnum.addr, align 8, !dbg !80
  %and = and i64 %0, 65535, !dbg !81
  %conv = trunc i64 %and to i16, !dbg !82
  ret i16 %conv, !dbg !83
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define zeroext i8 @curlx_ultouc(i64 %ulnum) #0 !dbg !22 {
entry:
  %ulnum.addr = alloca i64, align 8
  store i64 %ulnum, i64* %ulnum.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %ulnum.addr, metadata !84, metadata !74), !dbg !85
  br label %do.body, !dbg !86

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !87

do.end:                                           ; preds = %do.body
  %0 = load i64, i64* %ulnum.addr, align 8, !dbg !90
  %and = and i64 %0, 255, !dbg !91
  %conv = trunc i64 %and to i8, !dbg !92
  ret i8 %conv, !dbg !93
}

; Function Attrs: nounwind uwtable
define i32 @curlx_ultosi(i64 %ulnum) #0 !dbg !25 {
entry:
  %ulnum.addr = alloca i64, align 8
  store i64 %ulnum, i64* %ulnum.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %ulnum.addr, metadata !94, metadata !74), !dbg !95
  br label %do.body, !dbg !96

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !97

do.end:                                           ; preds = %do.body
  %0 = load i64, i64* %ulnum.addr, align 8, !dbg !100
  %and = and i64 %0, 2147483647, !dbg !101
  %conv = trunc i64 %and to i32, !dbg !102
  ret i32 %conv, !dbg !103
}

; Function Attrs: nounwind uwtable
define i64 @curlx_uztoso(i64 %uznum) #0 !dbg !28 {
entry:
  %uznum.addr = alloca i64, align 8
  store i64 %uznum, i64* %uznum.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %uznum.addr, metadata !104, metadata !74), !dbg !105
  br label %do.body, !dbg !106

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !107

do.end:                                           ; preds = %do.body
  %0 = load i64, i64* %uznum.addr, align 8, !dbg !110
  %and = and i64 %0, 9223372036854775807, !dbg !111
  ret i64 %and, !dbg !112
}

; Function Attrs: nounwind uwtable
define i32 @curlx_uztosi(i64 %uznum) #0 !dbg !31 {
entry:
  %uznum.addr = alloca i64, align 8
  store i64 %uznum, i64* %uznum.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %uznum.addr, metadata !113, metadata !74), !dbg !114
  br label %do.body, !dbg !115

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !116

do.end:                                           ; preds = %do.body
  %0 = load i64, i64* %uznum.addr, align 8, !dbg !119
  %and = and i64 %0, 2147483647, !dbg !120
  %conv = trunc i64 %and to i32, !dbg !121
  ret i32 %conv, !dbg !122
}

; Function Attrs: nounwind uwtable
define i64 @curlx_uztoul(i64 %uznum) #0 !dbg !34 {
entry:
  %uznum.addr = alloca i64, align 8
  store i64 %uznum, i64* %uznum.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %uznum.addr, metadata !123, metadata !74), !dbg !124
  %0 = load i64, i64* %uznum.addr, align 8, !dbg !125
  ret i64 %0, !dbg !126
}

; Function Attrs: nounwind uwtable
define i32 @curlx_uztoui(i64 %uznum) #0 !dbg !37 {
entry:
  %uznum.addr = alloca i64, align 8
  store i64 %uznum, i64* %uznum.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %uznum.addr, metadata !127, metadata !74), !dbg !128
  br label %do.body, !dbg !129

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !130

do.end:                                           ; preds = %do.body
  %0 = load i64, i64* %uznum.addr, align 8, !dbg !133
  %and = and i64 %0, 4294967295, !dbg !134
  %conv = trunc i64 %and to i32, !dbg !135
  ret i32 %conv, !dbg !136
}

; Function Attrs: nounwind uwtable
define i32 @curlx_sltosi(i64 %slnum) #0 !dbg !40 {
entry:
  %slnum.addr = alloca i64, align 8
  store i64 %slnum, i64* %slnum.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %slnum.addr, metadata !137, metadata !74), !dbg !138
  br label %do.body, !dbg !139

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !140

do.end:                                           ; preds = %do.body
  br label %do.body1, !dbg !143

do.body1:                                         ; preds = %do.end
  br label %do.end2, !dbg !144

do.end2:                                          ; preds = %do.body1
  %0 = load i64, i64* %slnum.addr, align 8, !dbg !147
  %and = and i64 %0, 2147483647, !dbg !148
  %conv = trunc i64 %and to i32, !dbg !149
  ret i32 %conv, !dbg !150
}

; Function Attrs: nounwind uwtable
define i32 @curlx_sltoui(i64 %slnum) #0 !dbg !43 {
entry:
  %slnum.addr = alloca i64, align 8
  store i64 %slnum, i64* %slnum.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %slnum.addr, metadata !151, metadata !74), !dbg !152
  br label %do.body, !dbg !153

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !154

do.end:                                           ; preds = %do.body
  br label %do.body1, !dbg !157

do.body1:                                         ; preds = %do.end
  br label %do.end2, !dbg !158

do.end2:                                          ; preds = %do.body1
  %0 = load i64, i64* %slnum.addr, align 8, !dbg !161
  %and = and i64 %0, 4294967295, !dbg !162
  %conv = trunc i64 %and to i32, !dbg !163
  ret i32 %conv, !dbg !164
}

; Function Attrs: nounwind uwtable
define zeroext i16 @curlx_sltous(i64 %slnum) #0 !dbg !46 {
entry:
  %slnum.addr = alloca i64, align 8
  store i64 %slnum, i64* %slnum.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %slnum.addr, metadata !165, metadata !74), !dbg !166
  br label %do.body, !dbg !167

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !168

do.end:                                           ; preds = %do.body
  br label %do.body1, !dbg !171

do.body1:                                         ; preds = %do.end
  br label %do.end2, !dbg !172

do.end2:                                          ; preds = %do.body1
  %0 = load i64, i64* %slnum.addr, align 8, !dbg !175
  %and = and i64 %0, 65535, !dbg !176
  %conv = trunc i64 %and to i16, !dbg !177
  ret i16 %conv, !dbg !178
}

; Function Attrs: nounwind uwtable
define i64 @curlx_uztosz(i64 %uznum) #0 !dbg !49 {
entry:
  %uznum.addr = alloca i64, align 8
  store i64 %uznum, i64* %uznum.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %uznum.addr, metadata !179, metadata !74), !dbg !180
  br label %do.body, !dbg !181

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !182

do.end:                                           ; preds = %do.body
  %0 = load i64, i64* %uznum.addr, align 8, !dbg !185
  %and = and i64 %0, 9223372036854775807, !dbg !186
  ret i64 %and, !dbg !187
}

; Function Attrs: nounwind uwtable
define i64 @curlx_sotouz(i64 %sonum) #0 !dbg !52 {
entry:
  %sonum.addr = alloca i64, align 8
  store i64 %sonum, i64* %sonum.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %sonum.addr, metadata !188, metadata !74), !dbg !189
  br label %do.body, !dbg !190

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !191

do.end:                                           ; preds = %do.body
  %0 = load i64, i64* %sonum.addr, align 8, !dbg !194
  ret i64 %0, !dbg !195
}

; Function Attrs: nounwind uwtable
define i32 @curlx_sztosi(i64 %sznum) #0 !dbg !55 {
entry:
  %sznum.addr = alloca i64, align 8
  store i64 %sznum, i64* %sznum.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %sznum.addr, metadata !196, metadata !74), !dbg !197
  br label %do.body, !dbg !198

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !199

do.end:                                           ; preds = %do.body
  br label %do.body1, !dbg !202

do.body1:                                         ; preds = %do.end
  br label %do.end2, !dbg !203

do.end2:                                          ; preds = %do.body1
  %0 = load i64, i64* %sznum.addr, align 8, !dbg !206
  %and = and i64 %0, 2147483647, !dbg !207
  %conv = trunc i64 %and to i32, !dbg !208
  ret i32 %conv, !dbg !209
}

; Function Attrs: nounwind uwtable
define zeroext i16 @curlx_uitous(i32 %uinum) #0 !dbg !58 {
entry:
  %uinum.addr = alloca i32, align 4
  store i32 %uinum, i32* %uinum.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %uinum.addr, metadata !210, metadata !74), !dbg !211
  br label %do.body, !dbg !212

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !213

do.end:                                           ; preds = %do.body
  %0 = load i32, i32* %uinum.addr, align 4, !dbg !216
  %and = and i32 %0, 65535, !dbg !217
  %conv = trunc i32 %and to i16, !dbg !218
  ret i16 %conv, !dbg !219
}

; Function Attrs: nounwind uwtable
define zeroext i8 @curlx_uitouc(i32 %uinum) #0 !dbg !61 {
entry:
  %uinum.addr = alloca i32, align 4
  store i32 %uinum, i32* %uinum.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %uinum.addr, metadata !220, metadata !74), !dbg !221
  br label %do.body, !dbg !222

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !223

do.end:                                           ; preds = %do.body
  %0 = load i32, i32* %uinum.addr, align 4, !dbg !226
  %and = and i32 %0, 255, !dbg !227
  %conv = trunc i32 %and to i8, !dbg !228
  ret i8 %conv, !dbg !229
}

; Function Attrs: nounwind uwtable
define i32 @curlx_uitosi(i32 %uinum) #0 !dbg !64 {
entry:
  %uinum.addr = alloca i32, align 4
  store i32 %uinum, i32* %uinum.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %uinum.addr, metadata !230, metadata !74), !dbg !231
  br label %do.body, !dbg !232

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !233

do.end:                                           ; preds = %do.body
  %0 = load i32, i32* %uinum.addr, align 4, !dbg !236
  %and = and i32 %0, 2147483647, !dbg !237
  ret i32 %and, !dbg !238
}

; Function Attrs: nounwind uwtable
define i64 @curlx_sitouz(i32 %sinum) #0 !dbg !67 {
entry:
  %sinum.addr = alloca i32, align 4
  store i32 %sinum, i32* %sinum.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sinum.addr, metadata !239, metadata !74), !dbg !240
  br label %do.body, !dbg !241

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !242

do.end:                                           ; preds = %do.body
  %0 = load i32, i32* %sinum.addr, align 4, !dbg !245
  %conv = sext i32 %0 to i64, !dbg !246
  ret i64 %conv, !dbg !247
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!70, !71}
!llvm.ident = !{!72}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !18)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/warnless.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{}
!3 = !{!4, !5, !6, !7, !8, !11, !13, !10, !14}
!4 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!5 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!6 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_off_t", file: !9, line: 216, baseType: !10)
!9 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curlbuild.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!10 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!11 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !12, line: 62, baseType: !5)
!12 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!13 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!14 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !15, line: 109, baseType: !16)
!15 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!16 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !17, line: 172, baseType: !10)
!17 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!18 = !{!19, !22, !25, !28, !31, !34, !37, !40, !43, !46, !49, !52, !55, !58, !61, !64, !67}
!19 = distinct !DISubprogram(name: "curlx_ultous", scope: !1, file: !1, line: 124, type: !20, isLocal: false, isDefinition: true, scopeLine: 125, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!20 = !DISubroutineType(types: !21)
!21 = !{!4, !5}
!22 = distinct !DISubprogram(name: "curlx_ultouc", scope: !1, file: !1, line: 143, type: !23, isLocal: false, isDefinition: true, scopeLine: 144, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!23 = !DISubroutineType(types: !24)
!24 = !{!6, !5}
!25 = distinct !DISubprogram(name: "curlx_ultosi", scope: !1, file: !1, line: 162, type: !26, isLocal: false, isDefinition: true, scopeLine: 163, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!26 = !DISubroutineType(types: !27)
!27 = !{!7, !5}
!28 = distinct !DISubprogram(name: "curlx_uztoso", scope: !1, file: !1, line: 181, type: !29, isLocal: false, isDefinition: true, scopeLine: 182, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!29 = !DISubroutineType(types: !30)
!30 = !{!8, !11}
!31 = distinct !DISubprogram(name: "curlx_uztosi", scope: !1, file: !1, line: 203, type: !32, isLocal: false, isDefinition: true, scopeLine: 204, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!32 = !DISubroutineType(types: !33)
!33 = !{!7, !11}
!34 = distinct !DISubprogram(name: "curlx_uztoul", scope: !1, file: !1, line: 222, type: !35, isLocal: false, isDefinition: true, scopeLine: 223, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!35 = !DISubroutineType(types: !36)
!36 = !{!5, !11}
!37 = distinct !DISubprogram(name: "curlx_uztoui", scope: !1, file: !1, line: 243, type: !38, isLocal: false, isDefinition: true, scopeLine: 244, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!38 = !DISubroutineType(types: !39)
!39 = !{!13, !11}
!40 = distinct !DISubprogram(name: "curlx_sltosi", scope: !1, file: !1, line: 264, type: !41, isLocal: false, isDefinition: true, scopeLine: 265, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!41 = !DISubroutineType(types: !42)
!42 = !{!7, !10}
!43 = distinct !DISubprogram(name: "curlx_sltoui", scope: !1, file: !1, line: 286, type: !44, isLocal: false, isDefinition: true, scopeLine: 287, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!44 = !DISubroutineType(types: !45)
!45 = !{!13, !10}
!46 = distinct !DISubprogram(name: "curlx_sltous", scope: !1, file: !1, line: 308, type: !47, isLocal: false, isDefinition: true, scopeLine: 309, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!47 = !DISubroutineType(types: !48)
!48 = !{!4, !10}
!49 = distinct !DISubprogram(name: "curlx_uztosz", scope: !1, file: !1, line: 328, type: !50, isLocal: false, isDefinition: true, scopeLine: 329, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!50 = !DISubroutineType(types: !51)
!51 = !{!14, !11}
!52 = distinct !DISubprogram(name: "curlx_sotouz", scope: !1, file: !1, line: 347, type: !53, isLocal: false, isDefinition: true, scopeLine: 348, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!53 = !DISubroutineType(types: !54)
!54 = !{!11, !8}
!55 = distinct !DISubprogram(name: "curlx_sztosi", scope: !1, file: !1, line: 366, type: !56, isLocal: false, isDefinition: true, scopeLine: 367, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!56 = !DISubroutineType(types: !57)
!57 = !{!7, !14}
!58 = distinct !DISubprogram(name: "curlx_uitous", scope: !1, file: !1, line: 388, type: !59, isLocal: false, isDefinition: true, scopeLine: 389, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!59 = !DISubroutineType(types: !60)
!60 = !{!4, !13}
!61 = distinct !DISubprogram(name: "curlx_uitouc", scope: !1, file: !1, line: 407, type: !62, isLocal: false, isDefinition: true, scopeLine: 408, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!62 = !DISubroutineType(types: !63)
!63 = !{!6, !13}
!64 = distinct !DISubprogram(name: "curlx_uitosi", scope: !1, file: !1, line: 426, type: !65, isLocal: false, isDefinition: true, scopeLine: 427, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!65 = !DISubroutineType(types: !66)
!66 = !{!7, !13}
!67 = distinct !DISubprogram(name: "curlx_sitouz", scope: !1, file: !1, line: 445, type: !68, isLocal: false, isDefinition: true, scopeLine: 446, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!68 = !DISubroutineType(types: !69)
!69 = !{!11, !7}
!70 = !{i32 2, !"Dwarf Version", i32 4}
!71 = !{i32 2, !"Debug Info Version", i32 3}
!72 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!73 = !DILocalVariable(name: "ulnum", arg: 1, scope: !19, file: !1, line: 124, type: !5)
!74 = !DIExpression()
!75 = !DILocation(line: 124, column: 43, scope: !19)
!76 = !DILocation(line: 131, column: 3, scope: !19)
!77 = !DILocation(line: 131, column: 3, scope: !78)
!78 = !DILexicalBlockFile(scope: !79, file: !1, discriminator: 1)
!79 = distinct !DILexicalBlock(scope: !19, file: !1, line: 131, column: 3)
!80 = !DILocation(line: 132, column: 27, scope: !19)
!81 = !DILocation(line: 132, column: 33, scope: !19)
!82 = !DILocation(line: 132, column: 10, scope: !19)
!83 = !DILocation(line: 132, column: 3, scope: !19)
!84 = !DILocalVariable(name: "ulnum", arg: 1, scope: !22, file: !1, line: 143, type: !5)
!85 = !DILocation(line: 143, column: 42, scope: !22)
!86 = !DILocation(line: 150, column: 3, scope: !22)
!87 = !DILocation(line: 150, column: 3, scope: !88)
!88 = !DILexicalBlockFile(scope: !89, file: !1, discriminator: 1)
!89 = distinct !DILexicalBlock(scope: !22, file: !1, line: 150, column: 3)
!90 = !DILocation(line: 151, column: 26, scope: !22)
!91 = !DILocation(line: 151, column: 32, scope: !22)
!92 = !DILocation(line: 151, column: 10, scope: !22)
!93 = !DILocation(line: 151, column: 3, scope: !22)
!94 = !DILocalVariable(name: "ulnum", arg: 1, scope: !25, file: !1, line: 162, type: !5)
!95 = !DILocation(line: 162, column: 32, scope: !25)
!96 = !DILocation(line: 169, column: 3, scope: !25)
!97 = !DILocation(line: 169, column: 3, scope: !98)
!98 = !DILexicalBlockFile(scope: !99, file: !1, discriminator: 1)
!99 = distinct !DILexicalBlock(scope: !25, file: !1, line: 169, column: 3)
!100 = !DILocation(line: 170, column: 16, scope: !25)
!101 = !DILocation(line: 170, column: 22, scope: !25)
!102 = !DILocation(line: 170, column: 10, scope: !25)
!103 = !DILocation(line: 170, column: 3, scope: !25)
!104 = !DILocalVariable(name: "uznum", arg: 1, scope: !28, file: !1, line: 181, type: !11)
!105 = !DILocation(line: 181, column: 32, scope: !28)
!106 = !DILocation(line: 191, column: 3, scope: !28)
!107 = !DILocation(line: 191, column: 3, scope: !108)
!108 = !DILexicalBlockFile(scope: !109, file: !1, discriminator: 1)
!109 = distinct !DILexicalBlock(scope: !28, file: !1, line: 191, column: 3)
!110 = !DILocation(line: 192, column: 23, scope: !28)
!111 = !DILocation(line: 192, column: 29, scope: !28)
!112 = !DILocation(line: 192, column: 3, scope: !28)
!113 = !DILocalVariable(name: "uznum", arg: 1, scope: !31, file: !1, line: 203, type: !11)
!114 = !DILocation(line: 203, column: 25, scope: !31)
!115 = !DILocation(line: 210, column: 3, scope: !31)
!116 = !DILocation(line: 210, column: 3, scope: !117)
!117 = !DILexicalBlockFile(scope: !118, file: !1, discriminator: 1)
!118 = distinct !DILexicalBlock(scope: !31, file: !1, line: 210, column: 3)
!119 = !DILocation(line: 211, column: 16, scope: !31)
!120 = !DILocation(line: 211, column: 22, scope: !31)
!121 = !DILocation(line: 211, column: 10, scope: !31)
!122 = !DILocation(line: 211, column: 3, scope: !31)
!123 = !DILocalVariable(name: "uznum", arg: 1, scope: !34, file: !1, line: 222, type: !11)
!124 = !DILocation(line: 222, column: 35, scope: !34)
!125 = !DILocation(line: 232, column: 26, scope: !34)
!126 = !DILocation(line: 232, column: 3, scope: !34)
!127 = !DILocalVariable(name: "uznum", arg: 1, scope: !37, file: !1, line: 243, type: !11)
!128 = !DILocation(line: 243, column: 34, scope: !37)
!129 = !DILocation(line: 251, column: 3, scope: !37)
!130 = !DILocation(line: 251, column: 3, scope: !131)
!131 = !DILexicalBlockFile(scope: !132, file: !1, discriminator: 1)
!132 = distinct !DILexicalBlock(scope: !37, file: !1, line: 251, column: 3)
!133 = !DILocation(line: 253, column: 25, scope: !37)
!134 = !DILocation(line: 253, column: 31, scope: !37)
!135 = !DILocation(line: 253, column: 10, scope: !37)
!136 = !DILocation(line: 253, column: 3, scope: !37)
!137 = !DILocalVariable(name: "slnum", arg: 1, scope: !40, file: !1, line: 264, type: !10)
!138 = !DILocation(line: 264, column: 23, scope: !40)
!139 = !DILocation(line: 271, column: 3, scope: !40)
!140 = !DILocation(line: 271, column: 3, scope: !141)
!141 = !DILexicalBlockFile(scope: !142, file: !1, discriminator: 1)
!142 = distinct !DILexicalBlock(scope: !40, file: !1, line: 271, column: 3)
!143 = !DILocation(line: 273, column: 3, scope: !40)
!144 = !DILocation(line: 273, column: 3, scope: !145)
!145 = !DILexicalBlockFile(scope: !146, file: !1, discriminator: 1)
!146 = distinct !DILexicalBlock(scope: !40, file: !1, line: 273, column: 3)
!147 = !DILocation(line: 275, column: 16, scope: !40)
!148 = !DILocation(line: 275, column: 22, scope: !40)
!149 = !DILocation(line: 275, column: 10, scope: !40)
!150 = !DILocation(line: 275, column: 3, scope: !40)
!151 = !DILocalVariable(name: "slnum", arg: 1, scope: !43, file: !1, line: 286, type: !10)
!152 = !DILocation(line: 286, column: 32, scope: !43)
!153 = !DILocation(line: 293, column: 3, scope: !43)
!154 = !DILocation(line: 293, column: 3, scope: !155)
!155 = !DILexicalBlockFile(scope: !156, file: !1, discriminator: 1)
!156 = distinct !DILexicalBlock(scope: !43, file: !1, line: 293, column: 3)
!157 = !DILocation(line: 295, column: 3, scope: !43)
!158 = !DILocation(line: 295, column: 3, scope: !159)
!159 = !DILexicalBlockFile(scope: !160, file: !1, discriminator: 1)
!160 = distinct !DILexicalBlock(scope: !43, file: !1, line: 295, column: 3)
!161 = !DILocation(line: 297, column: 25, scope: !43)
!162 = !DILocation(line: 297, column: 31, scope: !43)
!163 = !DILocation(line: 297, column: 10, scope: !43)
!164 = !DILocation(line: 297, column: 3, scope: !43)
!165 = !DILocalVariable(name: "slnum", arg: 1, scope: !46, file: !1, line: 308, type: !10)
!166 = !DILocation(line: 308, column: 34, scope: !46)
!167 = !DILocation(line: 315, column: 3, scope: !46)
!168 = !DILocation(line: 315, column: 3, scope: !169)
!169 = !DILexicalBlockFile(scope: !170, file: !1, discriminator: 1)
!170 = distinct !DILexicalBlock(scope: !46, file: !1, line: 315, column: 3)
!171 = !DILocation(line: 316, column: 3, scope: !46)
!172 = !DILocation(line: 316, column: 3, scope: !173)
!173 = !DILexicalBlockFile(scope: !174, file: !1, discriminator: 1)
!174 = distinct !DILexicalBlock(scope: !46, file: !1, line: 316, column: 3)
!175 = !DILocation(line: 317, column: 27, scope: !46)
!176 = !DILocation(line: 317, column: 33, scope: !46)
!177 = !DILocation(line: 317, column: 10, scope: !46)
!178 = !DILocation(line: 317, column: 3, scope: !46)
!179 = !DILocalVariable(name: "uznum", arg: 1, scope: !49, file: !1, line: 328, type: !11)
!180 = !DILocation(line: 328, column: 29, scope: !49)
!181 = !DILocation(line: 335, column: 3, scope: !49)
!182 = !DILocation(line: 335, column: 3, scope: !183)
!183 = !DILexicalBlockFile(scope: !184, file: !1, discriminator: 1)
!184 = distinct !DILexicalBlock(scope: !49, file: !1, line: 335, column: 3)
!185 = !DILocation(line: 336, column: 20, scope: !49)
!186 = !DILocation(line: 336, column: 26, scope: !49)
!187 = !DILocation(line: 336, column: 3, scope: !49)
!188 = !DILocalVariable(name: "sonum", arg: 1, scope: !52, file: !1, line: 347, type: !8)
!189 = !DILocation(line: 347, column: 32, scope: !52)
!190 = !DILocation(line: 354, column: 3, scope: !52)
!191 = !DILocation(line: 354, column: 3, scope: !192)
!192 = !DILexicalBlockFile(scope: !193, file: !1, discriminator: 1)
!193 = distinct !DILexicalBlock(scope: !52, file: !1, line: 354, column: 3)
!194 = !DILocation(line: 355, column: 19, scope: !52)
!195 = !DILocation(line: 355, column: 3, scope: !52)
!196 = !DILocalVariable(name: "sznum", arg: 1, scope: !55, file: !1, line: 366, type: !14)
!197 = !DILocation(line: 366, column: 26, scope: !55)
!198 = !DILocation(line: 373, column: 3, scope: !55)
!199 = !DILocation(line: 373, column: 3, scope: !200)
!200 = !DILexicalBlockFile(scope: !201, file: !1, discriminator: 1)
!201 = distinct !DILexicalBlock(scope: !55, file: !1, line: 373, column: 3)
!202 = !DILocation(line: 375, column: 3, scope: !55)
!203 = !DILocation(line: 375, column: 3, scope: !204)
!204 = !DILexicalBlockFile(scope: !205, file: !1, discriminator: 1)
!205 = distinct !DILexicalBlock(scope: !55, file: !1, line: 375, column: 3)
!206 = !DILocation(line: 377, column: 16, scope: !55)
!207 = !DILocation(line: 377, column: 22, scope: !55)
!208 = !DILocation(line: 377, column: 10, scope: !55)
!209 = !DILocation(line: 377, column: 3, scope: !55)
!210 = !DILocalVariable(name: "uinum", arg: 1, scope: !58, file: !1, line: 388, type: !13)
!211 = !DILocation(line: 388, column: 42, scope: !58)
!212 = !DILocation(line: 395, column: 3, scope: !58)
!213 = !DILocation(line: 395, column: 3, scope: !214)
!214 = !DILexicalBlockFile(scope: !215, file: !1, discriminator: 1)
!215 = distinct !DILexicalBlock(scope: !58, file: !1, line: 395, column: 3)
!216 = !DILocation(line: 396, column: 28, scope: !58)
!217 = !DILocation(line: 396, column: 34, scope: !58)
!218 = !DILocation(line: 396, column: 10, scope: !58)
!219 = !DILocation(line: 396, column: 3, scope: !58)
!220 = !DILocalVariable(name: "uinum", arg: 1, scope: !61, file: !1, line: 407, type: !13)
!221 = !DILocation(line: 407, column: 41, scope: !61)
!222 = !DILocation(line: 414, column: 3, scope: !61)
!223 = !DILocation(line: 414, column: 3, scope: !224)
!224 = !DILexicalBlockFile(scope: !225, file: !1, discriminator: 1)
!225 = distinct !DILexicalBlock(scope: !61, file: !1, line: 414, column: 3)
!226 = !DILocation(line: 415, column: 27, scope: !61)
!227 = !DILocation(line: 415, column: 33, scope: !61)
!228 = !DILocation(line: 415, column: 10, scope: !61)
!229 = !DILocation(line: 415, column: 3, scope: !61)
!230 = !DILocalVariable(name: "uinum", arg: 1, scope: !64, file: !1, line: 426, type: !13)
!231 = !DILocation(line: 426, column: 31, scope: !64)
!232 = !DILocation(line: 433, column: 3, scope: !64)
!233 = !DILocation(line: 433, column: 3, scope: !234)
!234 = !DILexicalBlockFile(scope: !235, file: !1, discriminator: 1)
!235 = distinct !DILexicalBlock(scope: !64, file: !1, line: 433, column: 3)
!236 = !DILocation(line: 434, column: 17, scope: !64)
!237 = !DILocation(line: 434, column: 23, scope: !64)
!238 = !DILocation(line: 434, column: 3, scope: !64)
!239 = !DILocalVariable(name: "sinum", arg: 1, scope: !67, file: !1, line: 445, type: !7)
!240 = !DILocation(line: 445, column: 25, scope: !67)
!241 = !DILocation(line: 452, column: 3, scope: !67)
!242 = !DILocation(line: 452, column: 3, scope: !243)
!243 = !DILexicalBlockFile(scope: !244, file: !1, discriminator: 1)
!244 = distinct !DILexicalBlock(scope: !67, file: !1, line: 452, column: 3)
!245 = !DILocation(line: 453, column: 19, scope: !67)
!246 = !DILocation(line: 453, column: 10, scope: !67)
!247 = !DILocation(line: 453, column: 3, scope: !67)
