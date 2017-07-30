; ModuleID = '/data/download/cmake/cmake-master/Source/kwsys/EncodingC.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i64 @cmsysEncoding_mbstowcs(i32* %dest, i8* %str, i64 %n) #0 !dbg !13 {
entry:
  %retval = alloca i64, align 8
  %dest.addr = alloca i32*, align 8
  %str.addr = alloca i8*, align 8
  %n.addr = alloca i64, align 8
  store i32* %dest, i32** %dest.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %dest.addr, metadata !32, metadata !33), !dbg !34
  store i8* %str, i8** %str.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %str.addr, metadata !35, metadata !33), !dbg !36
  store i64 %n, i64* %n.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %n.addr, metadata !37, metadata !33), !dbg !38
  %0 = load i8*, i8** %str.addr, align 8, !dbg !39
  %cmp = icmp eq i8* %0, null, !dbg !41
  br i1 %cmp, label %if.then, label %if.end, !dbg !42

if.then:                                          ; preds = %entry
  store i64 -1, i64* %retval, align 8, !dbg !43
  br label %return, !dbg !43

if.end:                                           ; preds = %entry
  %1 = load i32*, i32** %dest.addr, align 8, !dbg !45
  %2 = load i8*, i8** %str.addr, align 8, !dbg !46
  %3 = load i64, i64* %n.addr, align 8, !dbg !47
  %call = call i64 @mbstowcs(i32* %1, i8* %2, i64 %3) #3, !dbg !48
  store i64 %call, i64* %retval, align 8, !dbg !49
  br label %return, !dbg !49

return:                                           ; preds = %if.end, %if.then
  %4 = load i64, i64* %retval, align 8, !dbg !50
  ret i64 %4, !dbg !50
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare i64 @mbstowcs(i32*, i8*, i64) #2

; Function Attrs: nounwind uwtable
define i32* @cmsysEncoding_DupToWide(i8* %str) #0 !dbg !18 {
entry:
  %str.addr = alloca i8*, align 8
  %ret = alloca i32*, align 8
  %length = alloca i64, align 8
  store i8* %str, i8** %str.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %str.addr, metadata !51, metadata !33), !dbg !52
  call void @llvm.dbg.declare(metadata i32** %ret, metadata !53, metadata !33), !dbg !54
  store i32* null, i32** %ret, align 8, !dbg !54
  call void @llvm.dbg.declare(metadata i64* %length, metadata !55, metadata !33), !dbg !56
  %0 = load i8*, i8** %str.addr, align 8, !dbg !57
  %call = call i64 @cmsysEncoding_mbstowcs(i32* null, i8* %0, i64 0), !dbg !58
  %add = add i64 %call, 1, !dbg !59
  store i64 %add, i64* %length, align 8, !dbg !56
  %1 = load i64, i64* %length, align 8, !dbg !60
  %cmp = icmp ugt i64 %1, 0, !dbg !62
  br i1 %cmp, label %if.then, label %if.end4, !dbg !63

if.then:                                          ; preds = %entry
  %2 = load i64, i64* %length, align 8, !dbg !64
  %mul = mul i64 %2, 4, !dbg !66
  %call1 = call noalias i8* @malloc(i64 %mul) #3, !dbg !67
  %3 = bitcast i8* %call1 to i32*, !dbg !68
  store i32* %3, i32** %ret, align 8, !dbg !69
  %4 = load i32*, i32** %ret, align 8, !dbg !70
  %tobool = icmp ne i32* %4, null, !dbg !70
  br i1 %tobool, label %if.then2, label %if.end, !dbg !72

if.then2:                                         ; preds = %if.then
  %5 = load i32*, i32** %ret, align 8, !dbg !73
  %arrayidx = getelementptr inbounds i32, i32* %5, i64 0, !dbg !73
  store i32 0, i32* %arrayidx, align 4, !dbg !75
  %6 = load i32*, i32** %ret, align 8, !dbg !76
  %7 = load i8*, i8** %str.addr, align 8, !dbg !77
  %8 = load i64, i64* %length, align 8, !dbg !78
  %call3 = call i64 @cmsysEncoding_mbstowcs(i32* %6, i8* %7, i64 %8), !dbg !79
  br label %if.end, !dbg !80

if.end:                                           ; preds = %if.then2, %if.then
  br label %if.end4, !dbg !81

if.end4:                                          ; preds = %if.end, %entry
  %9 = load i32*, i32** %ret, align 8, !dbg !82
  ret i32* %9, !dbg !83
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #2

; Function Attrs: nounwind uwtable
define i64 @cmsysEncoding_wcstombs(i8* %dest, i32* %str, i64 %n) #0 !dbg !21 {
entry:
  %retval = alloca i64, align 8
  %dest.addr = alloca i8*, align 8
  %str.addr = alloca i32*, align 8
  %n.addr = alloca i64, align 8
  store i8* %dest, i8** %dest.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dest.addr, metadata !84, metadata !33), !dbg !85
  store i32* %str, i32** %str.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %str.addr, metadata !86, metadata !33), !dbg !87
  store i64 %n, i64* %n.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %n.addr, metadata !88, metadata !33), !dbg !89
  %0 = load i32*, i32** %str.addr, align 8, !dbg !90
  %cmp = icmp eq i32* %0, null, !dbg !92
  br i1 %cmp, label %if.then, label %if.end, !dbg !93

if.then:                                          ; preds = %entry
  store i64 -1, i64* %retval, align 8, !dbg !94
  br label %return, !dbg !94

if.end:                                           ; preds = %entry
  %1 = load i8*, i8** %dest.addr, align 8, !dbg !96
  %2 = load i32*, i32** %str.addr, align 8, !dbg !97
  %3 = load i64, i64* %n.addr, align 8, !dbg !98
  %call = call i64 @wcstombs(i8* %1, i32* %2, i64 %3) #3, !dbg !99
  store i64 %call, i64* %retval, align 8, !dbg !100
  br label %return, !dbg !100

return:                                           ; preds = %if.end, %if.then
  %4 = load i64, i64* %retval, align 8, !dbg !101
  ret i64 %4, !dbg !101
}

; Function Attrs: nounwind
declare i64 @wcstombs(i8*, i32*, i64) #2

; Function Attrs: nounwind uwtable
define i8* @cmsysEncoding_DupToNarrow(i32* %str) #0 !dbg !26 {
entry:
  %str.addr = alloca i32*, align 8
  %ret = alloca i8*, align 8
  %length = alloca i64, align 8
  store i32* %str, i32** %str.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %str.addr, metadata !102, metadata !33), !dbg !103
  call void @llvm.dbg.declare(metadata i8** %ret, metadata !104, metadata !33), !dbg !105
  store i8* null, i8** %ret, align 8, !dbg !105
  call void @llvm.dbg.declare(metadata i64* %length, metadata !106, metadata !33), !dbg !107
  %0 = load i32*, i32** %str.addr, align 8, !dbg !108
  %call = call i64 @cmsysEncoding_wcstombs(i8* null, i32* %0, i64 0), !dbg !109
  %add = add i64 %call, 1, !dbg !110
  store i64 %add, i64* %length, align 8, !dbg !107
  %1 = load i64, i64* %length, align 8, !dbg !111
  %cmp = icmp ugt i64 %1, 0, !dbg !113
  br i1 %cmp, label %if.then, label %if.end4, !dbg !114

if.then:                                          ; preds = %entry
  %2 = load i64, i64* %length, align 8, !dbg !115
  %call1 = call noalias i8* @malloc(i64 %2) #3, !dbg !117
  store i8* %call1, i8** %ret, align 8, !dbg !118
  %3 = load i8*, i8** %ret, align 8, !dbg !119
  %tobool = icmp ne i8* %3, null, !dbg !119
  br i1 %tobool, label %if.then2, label %if.end, !dbg !121

if.then2:                                         ; preds = %if.then
  %4 = load i8*, i8** %ret, align 8, !dbg !122
  %arrayidx = getelementptr inbounds i8, i8* %4, i64 0, !dbg !122
  store i8 0, i8* %arrayidx, align 1, !dbg !124
  %5 = load i8*, i8** %ret, align 8, !dbg !125
  %6 = load i32*, i32** %str.addr, align 8, !dbg !126
  %7 = load i64, i64* %length, align 8, !dbg !127
  %call3 = call i64 @cmsysEncoding_wcstombs(i8* %5, i32* %6, i64 %7), !dbg !128
  br label %if.end, !dbg !129

if.end:                                           ; preds = %if.then2, %if.then
  br label %if.end4, !dbg !130

if.end4:                                          ; preds = %if.end, %entry
  %8 = load i8*, i8** %ret, align 8, !dbg !131
  ret i8* %8, !dbg !132
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!29, !30}
!llvm.ident = !{!31}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !12)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Source/kwsys/EncodingC.c", directory: "/data/download/cmake/cmake-master/Source/kwsys")
!2 = !{}
!3 = !{!4, !7, !10}
!4 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !5, line: 62, baseType: !6)
!5 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Source/kwsys")
!6 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!7 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64, align: 64)
!8 = !DIDerivedType(tag: DW_TAG_typedef, name: "wchar_t", file: !5, line: 90, baseType: !9)
!9 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!11 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!12 = !{!13, !18, !21, !26}
!13 = distinct !DISubprogram(name: "cmsysEncoding_mbstowcs", scope: !1, file: !1, line: 18, type: !14, isLocal: false, isDefinition: true, scopeLine: 19, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!14 = !DISubroutineType(types: !15)
!15 = !{!4, !7, !16, !4}
!16 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !17, size: 64, align: 64)
!17 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !11)
!18 = distinct !DISubprogram(name: "cmsysEncoding_DupToWide", scope: !1, file: !1, line: 32, type: !19, isLocal: false, isDefinition: true, scopeLine: 33, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!19 = !DISubroutineType(types: !20)
!20 = !{!7, !16}
!21 = distinct !DISubprogram(name: "cmsysEncoding_wcstombs", scope: !1, file: !1, line: 46, type: !22, isLocal: false, isDefinition: true, scopeLine: 47, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!22 = !DISubroutineType(types: !23)
!23 = !{!4, !10, !24, !4}
!24 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !25, size: 64, align: 64)
!25 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !8)
!26 = distinct !DISubprogram(name: "cmsysEncoding_DupToNarrow", scope: !1, file: !1, line: 60, type: !27, isLocal: false, isDefinition: true, scopeLine: 61, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!27 = !DISubroutineType(types: !28)
!28 = !{!10, !24}
!29 = !{i32 2, !"Dwarf Version", i32 4}
!30 = !{i32 2, !"Debug Info Version", i32 3}
!31 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!32 = !DILocalVariable(name: "dest", arg: 1, scope: !13, file: !1, line: 18, type: !7)
!33 = !DIExpression()
!34 = !DILocation(line: 18, column: 40, scope: !13)
!35 = !DILocalVariable(name: "str", arg: 2, scope: !13, file: !1, line: 18, type: !16)
!36 = !DILocation(line: 18, column: 58, scope: !13)
!37 = !DILocalVariable(name: "n", arg: 3, scope: !13, file: !1, line: 18, type: !4)
!38 = !DILocation(line: 18, column: 70, scope: !13)
!39 = !DILocation(line: 20, column: 7, scope: !40)
!40 = distinct !DILexicalBlock(scope: !13, file: !1, line: 20, column: 7)
!41 = !DILocation(line: 20, column: 11, scope: !40)
!42 = !DILocation(line: 20, column: 7, scope: !13)
!43 = !DILocation(line: 21, column: 5, scope: !44)
!44 = distinct !DILexicalBlock(scope: !40, file: !1, line: 20, column: 17)
!45 = !DILocation(line: 28, column: 19, scope: !13)
!46 = !DILocation(line: 28, column: 25, scope: !13)
!47 = !DILocation(line: 28, column: 30, scope: !13)
!48 = !DILocation(line: 28, column: 10, scope: !13)
!49 = !DILocation(line: 28, column: 3, scope: !13)
!50 = !DILocation(line: 30, column: 1, scope: !13)
!51 = !DILocalVariable(name: "str", arg: 1, scope: !18, file: !1, line: 32, type: !16)
!52 = !DILocation(line: 32, column: 46, scope: !18)
!53 = !DILocalVariable(name: "ret", scope: !18, file: !1, line: 34, type: !7)
!54 = !DILocation(line: 34, column: 12, scope: !18)
!55 = !DILocalVariable(name: "length", scope: !18, file: !1, line: 35, type: !4)
!56 = !DILocation(line: 35, column: 10, scope: !18)
!57 = !DILocation(line: 35, column: 48, scope: !18)
!58 = !DILocation(line: 35, column: 19, scope: !18)
!59 = !DILocation(line: 35, column: 56, scope: !18)
!60 = !DILocation(line: 36, column: 7, scope: !61)
!61 = distinct !DILexicalBlock(scope: !18, file: !1, line: 36, column: 7)
!62 = !DILocation(line: 36, column: 14, scope: !61)
!63 = !DILocation(line: 36, column: 7, scope: !18)
!64 = !DILocation(line: 37, column: 29, scope: !65)
!65 = distinct !DILexicalBlock(scope: !61, file: !1, line: 36, column: 19)
!66 = !DILocation(line: 37, column: 37, scope: !65)
!67 = !DILocation(line: 37, column: 21, scope: !65)
!68 = !DILocation(line: 37, column: 11, scope: !65)
!69 = !DILocation(line: 37, column: 9, scope: !65)
!70 = !DILocation(line: 38, column: 9, scope: !71)
!71 = distinct !DILexicalBlock(scope: !65, file: !1, line: 38, column: 9)
!72 = !DILocation(line: 38, column: 9, scope: !65)
!73 = !DILocation(line: 39, column: 7, scope: !74)
!74 = distinct !DILexicalBlock(scope: !71, file: !1, line: 38, column: 14)
!75 = !DILocation(line: 39, column: 14, scope: !74)
!76 = !DILocation(line: 40, column: 30, scope: !74)
!77 = !DILocation(line: 40, column: 35, scope: !74)
!78 = !DILocation(line: 40, column: 40, scope: !74)
!79 = !DILocation(line: 40, column: 7, scope: !74)
!80 = !DILocation(line: 41, column: 5, scope: !74)
!81 = !DILocation(line: 42, column: 3, scope: !65)
!82 = !DILocation(line: 43, column: 10, scope: !18)
!83 = !DILocation(line: 43, column: 3, scope: !18)
!84 = !DILocalVariable(name: "dest", arg: 1, scope: !21, file: !1, line: 46, type: !10)
!85 = !DILocation(line: 46, column: 37, scope: !21)
!86 = !DILocalVariable(name: "str", arg: 2, scope: !21, file: !1, line: 46, type: !24)
!87 = !DILocation(line: 46, column: 58, scope: !21)
!88 = !DILocalVariable(name: "n", arg: 3, scope: !21, file: !1, line: 46, type: !4)
!89 = !DILocation(line: 46, column: 70, scope: !21)
!90 = !DILocation(line: 48, column: 7, scope: !91)
!91 = distinct !DILexicalBlock(scope: !21, file: !1, line: 48, column: 7)
!92 = !DILocation(line: 48, column: 11, scope: !91)
!93 = !DILocation(line: 48, column: 7, scope: !21)
!94 = !DILocation(line: 49, column: 5, scope: !95)
!95 = distinct !DILexicalBlock(scope: !91, file: !1, line: 48, column: 17)
!96 = !DILocation(line: 56, column: 19, scope: !21)
!97 = !DILocation(line: 56, column: 25, scope: !21)
!98 = !DILocation(line: 56, column: 30, scope: !21)
!99 = !DILocation(line: 56, column: 10, scope: !21)
!100 = !DILocation(line: 56, column: 3, scope: !21)
!101 = !DILocation(line: 58, column: 1, scope: !21)
!102 = !DILocalVariable(name: "str", arg: 1, scope: !26, file: !1, line: 60, type: !24)
!103 = !DILocation(line: 60, column: 48, scope: !26)
!104 = !DILocalVariable(name: "ret", scope: !26, file: !1, line: 62, type: !10)
!105 = !DILocation(line: 62, column: 9, scope: !26)
!106 = !DILocalVariable(name: "length", scope: !26, file: !1, line: 63, type: !4)
!107 = !DILocation(line: 63, column: 10, scope: !26)
!108 = !DILocation(line: 63, column: 45, scope: !26)
!109 = !DILocation(line: 63, column: 19, scope: !26)
!110 = !DILocation(line: 63, column: 53, scope: !26)
!111 = !DILocation(line: 64, column: 7, scope: !112)
!112 = distinct !DILexicalBlock(scope: !26, file: !1, line: 64, column: 7)
!113 = !DILocation(line: 64, column: 14, scope: !112)
!114 = !DILocation(line: 64, column: 7, scope: !26)
!115 = !DILocation(line: 65, column: 25, scope: !116)
!116 = distinct !DILexicalBlock(scope: !112, file: !1, line: 64, column: 19)
!117 = !DILocation(line: 65, column: 18, scope: !116)
!118 = !DILocation(line: 65, column: 9, scope: !116)
!119 = !DILocation(line: 66, column: 9, scope: !120)
!120 = distinct !DILexicalBlock(scope: !116, file: !1, line: 66, column: 9)
!121 = !DILocation(line: 66, column: 9, scope: !116)
!122 = !DILocation(line: 67, column: 7, scope: !123)
!123 = distinct !DILexicalBlock(scope: !120, file: !1, line: 66, column: 14)
!124 = !DILocation(line: 67, column: 14, scope: !123)
!125 = !DILocation(line: 68, column: 30, scope: !123)
!126 = !DILocation(line: 68, column: 35, scope: !123)
!127 = !DILocation(line: 68, column: 40, scope: !123)
!128 = !DILocation(line: 68, column: 7, scope: !123)
!129 = !DILocation(line: 69, column: 5, scope: !123)
!130 = !DILocation(line: 70, column: 3, scope: !116)
!131 = !DILocation(line: 71, column: 10, scope: !26)
!132 = !DILocation(line: 71, column: 3, scope: !26)
