; ModuleID = '/data/download/cmake/cmake-master/Source/cm_utf8.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@cm_utf8_ones = internal constant [256 x i8] c"\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\02\02\02\02\02\02\02\02\02\02\02\02\02\02\02\02\02\02\02\02\02\02\02\02\02\02\02\02\02\02\02\02\03\03\03\03\03\03\03\03\03\03\03\03\03\03\03\03\04\04\04\04\04\04\04\04\05\05\05\05\06\06\07\08", align 16
@cm_utf8_mask = internal constant [7 x i8] c"\EF?\1F\0F\07\03\01", align 1
@cm_utf8_min = internal constant [7 x i32] [i32 0, i32 0, i32 128, i32 2048, i32 65536, i32 2097152, i32 67108864], align 16

; Function Attrs: nounwind uwtable
define i8* @cm_utf8_decode_character(i8* %first, i8* %last, i32* %pc) #0 !dbg !6 {
entry:
  %retval = alloca i8*, align 8
  %first.addr = alloca i8*, align 8
  %last.addr = alloca i8*, align 8
  %pc.addr = alloca i32*, align 8
  %c = alloca i8, align 1
  %ones = alloca i8, align 1
  %uc = alloca i32, align 4
  %left = alloca i32, align 4
  store i8* %first, i8** %first.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %first.addr, metadata !30, metadata !31), !dbg !32
  store i8* %last, i8** %last.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %last.addr, metadata !33, metadata !31), !dbg !34
  store i32* %pc, i32** %pc.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %pc.addr, metadata !35, metadata !31), !dbg !36
  call void @llvm.dbg.declare(metadata i8* %c, metadata !37, metadata !31), !dbg !38
  %0 = load i8*, i8** %first.addr, align 8, !dbg !39
  %incdec.ptr = getelementptr inbounds i8, i8* %0, i32 1, !dbg !39
  store i8* %incdec.ptr, i8** %first.addr, align 8, !dbg !39
  %1 = load i8, i8* %0, align 1, !dbg !40
  store i8 %1, i8* %c, align 1, !dbg !38
  call void @llvm.dbg.declare(metadata i8* %ones, metadata !41, metadata !31), !dbg !42
  %2 = load i8, i8* %c, align 1, !dbg !43
  %idxprom = zext i8 %2 to i64, !dbg !44
  %arrayidx = getelementptr inbounds [256 x i8], [256 x i8]* @cm_utf8_ones, i64 0, i64 %idxprom, !dbg !44
  %3 = load i8, i8* %arrayidx, align 1, !dbg !44
  store i8 %3, i8* %ones, align 1, !dbg !42
  %4 = load i8, i8* %ones, align 1, !dbg !45
  %conv = zext i8 %4 to i32, !dbg !45
  switch i32 %conv, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb2
    i32 7, label %sw.bb2
    i32 8, label %sw.bb2
  ], !dbg !46

sw.bb:                                            ; preds = %entry
  %5 = load i8, i8* %c, align 1, !dbg !47
  %conv1 = zext i8 %5 to i32, !dbg !47
  %6 = load i32*, i32** %pc.addr, align 8, !dbg !49
  store i32 %conv1, i32* %6, align 4, !dbg !50
  %7 = load i8*, i8** %first.addr, align 8, !dbg !51
  store i8* %7, i8** %retval, align 8, !dbg !52
  br label %return, !dbg !52

sw.bb2:                                           ; preds = %entry, %entry, %entry
  store i8* null, i8** %retval, align 8, !dbg !53
  br label %return, !dbg !53

sw.default:                                       ; preds = %entry
  br label %sw.epilog, !dbg !54

sw.epilog:                                        ; preds = %sw.default
  call void @llvm.dbg.declare(metadata i32* %uc, metadata !55, metadata !31), !dbg !57
  %8 = load i8, i8* %c, align 1, !dbg !58
  %conv3 = zext i8 %8 to i32, !dbg !58
  %9 = load i8, i8* %ones, align 1, !dbg !59
  %idxprom4 = zext i8 %9 to i64, !dbg !60
  %arrayidx5 = getelementptr inbounds [7 x i8], [7 x i8]* @cm_utf8_mask, i64 0, i64 %idxprom4, !dbg !60
  %10 = load i8, i8* %arrayidx5, align 1, !dbg !60
  %conv6 = zext i8 %10 to i32, !dbg !60
  %and = and i32 %conv3, %conv6, !dbg !61
  store i32 %and, i32* %uc, align 4, !dbg !57
  call void @llvm.dbg.declare(metadata i32* %left, metadata !62, metadata !31), !dbg !64
  %11 = load i8, i8* %ones, align 1, !dbg !65
  %conv7 = zext i8 %11 to i32, !dbg !65
  %sub = sub nsw i32 %conv7, 1, !dbg !67
  store i32 %sub, i32* %left, align 4, !dbg !68
  br label %for.cond, !dbg !69

for.cond:                                         ; preds = %for.inc, %sw.epilog
  %12 = load i32, i32* %left, align 4, !dbg !70
  %tobool = icmp ne i32 %12, 0, !dbg !70
  br i1 %tobool, label %land.rhs, label %land.end, !dbg !73

land.rhs:                                         ; preds = %for.cond
  %13 = load i8*, i8** %first.addr, align 8, !dbg !74
  %14 = load i8*, i8** %last.addr, align 8, !dbg !76
  %cmp = icmp ne i8* %13, %14, !dbg !77
  br label %land.end

land.end:                                         ; preds = %land.rhs, %for.cond
  %15 = phi i1 [ false, %for.cond ], [ %cmp, %land.rhs ]
  br i1 %15, label %for.body, label %for.end, !dbg !78

for.body:                                         ; preds = %land.end
  %16 = load i8*, i8** %first.addr, align 8, !dbg !80
  %incdec.ptr9 = getelementptr inbounds i8, i8* %16, i32 1, !dbg !80
  store i8* %incdec.ptr9, i8** %first.addr, align 8, !dbg !80
  %17 = load i8, i8* %16, align 1, !dbg !82
  store i8 %17, i8* %c, align 1, !dbg !83
  %18 = load i8, i8* %c, align 1, !dbg !84
  %idxprom10 = zext i8 %18 to i64, !dbg !86
  %arrayidx11 = getelementptr inbounds [256 x i8], [256 x i8]* @cm_utf8_ones, i64 0, i64 %idxprom10, !dbg !86
  %19 = load i8, i8* %arrayidx11, align 1, !dbg !86
  %conv12 = zext i8 %19 to i32, !dbg !86
  %cmp13 = icmp ne i32 %conv12, 1, !dbg !87
  br i1 %cmp13, label %if.then, label %if.end, !dbg !88

if.then:                                          ; preds = %for.body
  store i8* null, i8** %retval, align 8, !dbg !89
  br label %return, !dbg !89

if.end:                                           ; preds = %for.body
  %20 = load i32, i32* %uc, align 4, !dbg !91
  %shl = shl i32 %20, 6, !dbg !92
  %21 = load i8, i8* %c, align 1, !dbg !93
  %conv15 = zext i8 %21 to i32, !dbg !93
  %22 = load i8, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @cm_utf8_mask, i64 0, i64 1), align 1, !dbg !94
  %conv16 = zext i8 %22 to i32, !dbg !94
  %and17 = and i32 %conv15, %conv16, !dbg !95
  %or = or i32 %shl, %and17, !dbg !96
  store i32 %or, i32* %uc, align 4, !dbg !97
  br label %for.inc, !dbg !98

for.inc:                                          ; preds = %if.end
  %23 = load i32, i32* %left, align 4, !dbg !99
  %dec = add nsw i32 %23, -1, !dbg !99
  store i32 %dec, i32* %left, align 4, !dbg !99
  br label %for.cond, !dbg !101

for.end:                                          ; preds = %land.end
  %24 = load i32, i32* %left, align 4, !dbg !102
  %cmp18 = icmp sgt i32 %24, 0, !dbg !104
  br i1 %cmp18, label %if.then24, label %lor.lhs.false, !dbg !105

lor.lhs.false:                                    ; preds = %for.end
  %25 = load i32, i32* %uc, align 4, !dbg !106
  %26 = load i8, i8* %ones, align 1, !dbg !108
  %idxprom20 = zext i8 %26 to i64, !dbg !109
  %arrayidx21 = getelementptr inbounds [7 x i32], [7 x i32]* @cm_utf8_min, i64 0, i64 %idxprom20, !dbg !109
  %27 = load i32, i32* %arrayidx21, align 4, !dbg !109
  %cmp22 = icmp ult i32 %25, %27, !dbg !110
  br i1 %cmp22, label %if.then24, label %if.end25, !dbg !111

if.then24:                                        ; preds = %lor.lhs.false, %for.end
  store i8* null, i8** %retval, align 8, !dbg !112
  br label %return, !dbg !112

if.end25:                                         ; preds = %lor.lhs.false
  %28 = load i32, i32* %uc, align 4, !dbg !114
  %29 = load i32*, i32** %pc.addr, align 8, !dbg !115
  store i32 %28, i32* %29, align 4, !dbg !116
  %30 = load i8*, i8** %first.addr, align 8, !dbg !117
  store i8* %30, i8** %retval, align 8, !dbg !118
  br label %return, !dbg !118

return:                                           ; preds = %if.end25, %if.then24, %if.then, %sw.bb2, %sw.bb
  %31 = load i8*, i8** %retval, align 8, !dbg !119
  ret i8* %31, !dbg !119
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!27, !28}
!llvm.ident = !{!29}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !5, globals: !14)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Source/cm_utf8.c", directory: "/data/download/cmake/cmake-master/Source")
!2 = !{}
!3 = !{!4}
!4 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!5 = !{!6}
!6 = distinct !DISubprogram(name: "cm_utf8_decode_character", scope: !1, file: !1, line: 40, type: !7, isLocal: false, isDefinition: true, scopeLine: 42, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!7 = !DISubroutineType(types: !8)
!8 = !{!9, !9, !9, !12}
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !11)
!11 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!12 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !13, size: 64, align: 64)
!13 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!14 = !{!15, !20, !24}
!15 = !DIGlobalVariable(name: "cm_utf8_ones", scope: !0, file: !1, line: 18, type: !16, isLocal: true, isDefinition: true, variable: [256 x i8]* @cm_utf8_ones)
!16 = !DICompositeType(tag: DW_TAG_array_type, baseType: !17, size: 2048, align: 8, elements: !18)
!17 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !4)
!18 = !{!19}
!19 = !DISubrange(count: 256)
!20 = !DIGlobalVariable(name: "cm_utf8_mask", scope: !0, file: !1, line: 32, type: !21, isLocal: true, isDefinition: true, variable: [7 x i8]* @cm_utf8_mask)
!21 = !DICompositeType(tag: DW_TAG_array_type, baseType: !17, size: 56, align: 8, elements: !22)
!22 = !{!23}
!23 = !DISubrange(count: 7)
!24 = !DIGlobalVariable(name: "cm_utf8_min", scope: !0, file: !1, line: 36, type: !25, isLocal: true, isDefinition: true, variable: [7 x i32]* @cm_utf8_min)
!25 = !DICompositeType(tag: DW_TAG_array_type, baseType: !26, size: 224, align: 32, elements: !22)
!26 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !13)
!27 = !{i32 2, !"Dwarf Version", i32 4}
!28 = !{i32 2, !"Debug Info Version", i32 3}
!29 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!30 = !DILocalVariable(name: "first", arg: 1, scope: !6, file: !1, line: 40, type: !9)
!31 = !DIExpression()
!32 = !DILocation(line: 40, column: 50, scope: !6)
!33 = !DILocalVariable(name: "last", arg: 2, scope: !6, file: !1, line: 40, type: !9)
!34 = !DILocation(line: 40, column: 69, scope: !6)
!35 = !DILocalVariable(name: "pc", arg: 3, scope: !6, file: !1, line: 41, type: !12)
!36 = !DILocation(line: 41, column: 52, scope: !6)
!37 = !DILocalVariable(name: "c", scope: !6, file: !1, line: 44, type: !4)
!38 = !DILocation(line: 44, column: 17, scope: !6)
!39 = !DILocation(line: 44, column: 42, scope: !6)
!40 = !DILocation(line: 44, column: 36, scope: !6)
!41 = !DILocalVariable(name: "ones", scope: !6, file: !1, line: 45, type: !17)
!42 = !DILocation(line: 45, column: 23, scope: !6)
!43 = !DILocation(line: 45, column: 43, scope: !6)
!44 = !DILocation(line: 45, column: 30, scope: !6)
!45 = !DILocation(line: 46, column: 11, scope: !6)
!46 = !DILocation(line: 46, column: 3, scope: !6)
!47 = !DILocation(line: 48, column: 13, scope: !48)
!48 = distinct !DILexicalBlock(scope: !6, file: !1, line: 46, column: 17)
!49 = !DILocation(line: 48, column: 8, scope: !48)
!50 = !DILocation(line: 48, column: 11, scope: !48)
!51 = !DILocation(line: 49, column: 14, scope: !48)
!52 = !DILocation(line: 49, column: 7, scope: !48)
!53 = !DILocation(line: 53, column: 7, scope: !48)
!54 = !DILocation(line: 55, column: 7, scope: !48)
!55 = !DILocalVariable(name: "uc", scope: !56, file: !1, line: 60, type: !13)
!56 = distinct !DILexicalBlock(scope: !6, file: !1, line: 59, column: 3)
!57 = !DILocation(line: 60, column: 18, scope: !56)
!58 = !DILocation(line: 60, column: 23, scope: !56)
!59 = !DILocation(line: 60, column: 40, scope: !56)
!60 = !DILocation(line: 60, column: 27, scope: !56)
!61 = !DILocation(line: 60, column: 25, scope: !56)
!62 = !DILocalVariable(name: "left", scope: !56, file: !1, line: 61, type: !63)
!63 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!64 = !DILocation(line: 61, column: 9, scope: !56)
!65 = !DILocation(line: 62, column: 17, scope: !66)
!66 = distinct !DILexicalBlock(scope: !56, file: !1, line: 62, column: 5)
!67 = !DILocation(line: 62, column: 22, scope: !66)
!68 = !DILocation(line: 62, column: 15, scope: !66)
!69 = !DILocation(line: 62, column: 10, scope: !66)
!70 = !DILocation(line: 62, column: 27, scope: !71)
!71 = !DILexicalBlockFile(scope: !72, file: !1, discriminator: 1)
!72 = distinct !DILexicalBlock(scope: !66, file: !1, line: 62, column: 5)
!73 = !DILocation(line: 62, column: 32, scope: !71)
!74 = !DILocation(line: 62, column: 35, scope: !75)
!75 = !DILexicalBlockFile(scope: !72, file: !1, discriminator: 2)
!76 = !DILocation(line: 62, column: 44, scope: !75)
!77 = !DILocation(line: 62, column: 41, scope: !75)
!78 = !DILocation(line: 62, column: 5, scope: !79)
!79 = !DILexicalBlockFile(scope: !66, file: !1, discriminator: 3)
!80 = !DILocation(line: 63, column: 32, scope: !81)
!81 = distinct !DILexicalBlock(scope: !72, file: !1, line: 62, column: 58)
!82 = !DILocation(line: 63, column: 26, scope: !81)
!83 = !DILocation(line: 63, column: 9, scope: !81)
!84 = !DILocation(line: 64, column: 24, scope: !85)
!85 = distinct !DILexicalBlock(scope: !81, file: !1, line: 64, column: 11)
!86 = !DILocation(line: 64, column: 11, scope: !85)
!87 = !DILocation(line: 64, column: 27, scope: !85)
!88 = !DILocation(line: 64, column: 11, scope: !81)
!89 = !DILocation(line: 65, column: 9, scope: !90)
!90 = distinct !DILexicalBlock(scope: !85, file: !1, line: 64, column: 33)
!91 = !DILocation(line: 67, column: 13, scope: !81)
!92 = !DILocation(line: 67, column: 16, scope: !81)
!93 = !DILocation(line: 67, column: 25, scope: !81)
!94 = !DILocation(line: 67, column: 29, scope: !81)
!95 = !DILocation(line: 67, column: 27, scope: !81)
!96 = !DILocation(line: 67, column: 22, scope: !81)
!97 = !DILocation(line: 67, column: 10, scope: !81)
!98 = !DILocation(line: 68, column: 5, scope: !81)
!99 = !DILocation(line: 62, column: 50, scope: !100)
!100 = !DILexicalBlockFile(scope: !72, file: !1, discriminator: 4)
!101 = !DILocation(line: 62, column: 5, scope: !100)
!102 = !DILocation(line: 70, column: 9, scope: !103)
!103 = distinct !DILexicalBlock(scope: !56, file: !1, line: 70, column: 9)
!104 = !DILocation(line: 70, column: 14, scope: !103)
!105 = !DILocation(line: 70, column: 18, scope: !103)
!106 = !DILocation(line: 70, column: 21, scope: !107)
!107 = !DILexicalBlockFile(scope: !103, file: !1, discriminator: 1)
!108 = !DILocation(line: 70, column: 38, scope: !107)
!109 = !DILocation(line: 70, column: 26, scope: !107)
!110 = !DILocation(line: 70, column: 24, scope: !107)
!111 = !DILocation(line: 70, column: 9, scope: !107)
!112 = !DILocation(line: 71, column: 7, scope: !113)
!113 = distinct !DILexicalBlock(scope: !103, file: !1, line: 70, column: 45)
!114 = !DILocation(line: 74, column: 11, scope: !56)
!115 = !DILocation(line: 74, column: 6, scope: !56)
!116 = !DILocation(line: 74, column: 9, scope: !56)
!117 = !DILocation(line: 75, column: 12, scope: !56)
!118 = !DILocation(line: 75, column: 5, scope: !56)
!119 = !DILocation(line: 77, column: 1, scope: !6)
