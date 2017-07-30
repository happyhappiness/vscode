; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmzlib/zutil.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [16 x i8] c"need dictionary\00", align 1
@.str.1 = private unnamed_addr constant [11 x i8] c"stream end\00", align 1
@.str.2 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.3 = private unnamed_addr constant [11 x i8] c"file error\00", align 1
@.str.4 = private unnamed_addr constant [13 x i8] c"stream error\00", align 1
@.str.5 = private unnamed_addr constant [11 x i8] c"data error\00", align 1
@.str.6 = private unnamed_addr constant [20 x i8] c"insufficient memory\00", align 1
@.str.7 = private unnamed_addr constant [13 x i8] c"buffer error\00", align 1
@.str.8 = private unnamed_addr constant [21 x i8] c"incompatible version\00", align 1
@cm_zlib_z_errmsg = constant [10 x i8*] [i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.1, i32 0, i32 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.7, i32 0, i32 0), i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.2, i32 0, i32 0)], align 16
@.str.9 = private unnamed_addr constant [6 x i8] c"1.2.3\00", align 1

; Function Attrs: nounwind uwtable
define i8* @cm_zlib_zlibVersion() #0 !dbg !8 {
entry:
  ret i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.9, i32 0, i32 0), !dbg !39
}

; Function Attrs: nounwind uwtable
define i64 @cm_zlib_zlibCompileFlags() #0 !dbg !14 {
entry:
  %flags = alloca i64, align 8
  call void @llvm.dbg.declare(metadata i64* %flags, metadata !40, metadata !41), !dbg !42
  store i64 0, i64* %flags, align 8, !dbg !43
  %0 = load i64, i64* %flags, align 8, !dbg !44
  %add = add i64 %0, 1, !dbg !44
  store i64 %add, i64* %flags, align 8, !dbg !44
  %1 = load i64, i64* %flags, align 8, !dbg !45
  %add1 = add i64 %1, 8, !dbg !45
  store i64 %add1, i64* %flags, align 8, !dbg !45
  %2 = load i64, i64* %flags, align 8, !dbg !46
  %add2 = add i64 %2, 32, !dbg !46
  store i64 %add2, i64* %flags, align 8, !dbg !46
  %3 = load i64, i64* %flags, align 8, !dbg !47
  %add3 = add i64 %3, 128, !dbg !47
  store i64 %add3, i64* %flags, align 8, !dbg !47
  %4 = load i64, i64* %flags, align 8, !dbg !48
  ret i64 %4, !dbg !49
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i8* @cm_zlib_zError(i32 %err) #0 !dbg !19 {
entry:
  %err.addr = alloca i32, align 4
  store i32 %err, i32* %err.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %err.addr, metadata !50, metadata !41), !dbg !51
  %0 = load i32, i32* %err.addr, align 4, !dbg !52
  %sub = sub nsw i32 2, %0, !dbg !52
  %idxprom = sext i32 %sub to i64, !dbg !52
  %arrayidx = getelementptr inbounds [10 x i8*], [10 x i8*]* @cm_zlib_z_errmsg, i64 0, i64 %idxprom, !dbg !52
  %1 = load i8*, i8** %arrayidx, align 8, !dbg !52
  ret i8* %1, !dbg !53
}

; Function Attrs: nounwind uwtable
define i8* @cm_zlib_zcalloc(i8* %opaque, i32 %items, i32 %size) #0 !dbg !23 {
entry:
  %opaque.addr = alloca i8*, align 8
  %items.addr = alloca i32, align 4
  %size.addr = alloca i32, align 4
  store i8* %opaque, i8** %opaque.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %opaque.addr, metadata !54, metadata !41), !dbg !55
  store i32 %items, i32* %items.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %items.addr, metadata !56, metadata !41), !dbg !57
  store i32 %size, i32* %size.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %size.addr, metadata !58, metadata !41), !dbg !59
  %0 = load i8*, i8** %opaque.addr, align 8, !dbg !60
  %tobool = icmp ne i8* %0, null, !dbg !60
  br i1 %tobool, label %if.then, label %if.end, !dbg !62

if.then:                                          ; preds = %entry
  %1 = load i32, i32* %size.addr, align 4, !dbg !63
  %2 = load i32, i32* %size.addr, align 4, !dbg !65
  %sub = sub i32 %1, %2, !dbg !66
  %3 = load i32, i32* %items.addr, align 4, !dbg !67
  %add = add i32 %3, %sub, !dbg !67
  store i32 %add, i32* %items.addr, align 4, !dbg !67
  br label %if.end, !dbg !68

if.end:                                           ; preds = %if.then, %entry
  %4 = load i32, i32* %items.addr, align 4, !dbg !69
  %5 = load i32, i32* %size.addr, align 4, !dbg !70
  %mul = mul i32 %4, %5, !dbg !71
  %conv = zext i32 %mul to i64, !dbg !69
  %call = call noalias i8* @malloc(i64 %conv) #3, !dbg !72
  ret i8* %call, !dbg !73
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #2

; Function Attrs: nounwind uwtable
define void @cm_zlib_zcfree(i8* %opaque, i8* %ptr) #0 !dbg !27 {
entry:
  %opaque.addr = alloca i8*, align 8
  %ptr.addr = alloca i8*, align 8
  store i8* %opaque, i8** %opaque.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %opaque.addr, metadata !74, metadata !41), !dbg !75
  store i8* %ptr, i8** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr.addr, metadata !76, metadata !41), !dbg !77
  %0 = load i8*, i8** %ptr.addr, align 8, !dbg !78
  call void @free(i8* %0) #3, !dbg !79
  %1 = load i8*, i8** %opaque.addr, align 8, !dbg !80
  %tobool = icmp ne i8* %1, null, !dbg !80
  br i1 %tobool, label %if.then, label %if.end, !dbg !82

if.then:                                          ; preds = %entry
  br label %if.end, !dbg !83

if.end:                                           ; preds = %if.then, %entry
  ret void, !dbg !85
}

; Function Attrs: nounwind
declare void @free(i8*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!36, !37}
!llvm.ident = !{!38}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !7, globals: !30)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/zutil.c", directory: "/data/download/cmake/cmake-master/Utilities/cmzlib")
!2 = !{}
!3 = !{!4}
!4 = !DIDerivedType(tag: DW_TAG_typedef, name: "voidpf", file: !5, line: 285, baseType: !6)
!5 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/zconf.h", directory: "/data/download/cmake/cmake-master/Utilities/cmzlib")
!6 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!7 = !{!8, !14, !19, !23, !27}
!8 = distinct !DISubprogram(name: "cm_zlib_zlibVersion", scope: !1, file: !1, line: 27, type: !9, isLocal: false, isDefinition: true, scopeLine: 28, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!9 = !DISubroutineType(types: !10)
!10 = !{!11}
!11 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !12, size: 64, align: 64)
!12 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !13)
!13 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!14 = distinct !DISubprogram(name: "cm_zlib_zlibCompileFlags", scope: !1, file: !1, line: 32, type: !15, isLocal: false, isDefinition: true, scopeLine: 33, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!15 = !DISubroutineType(types: !16)
!16 = !{!17}
!17 = !DIDerivedType(tag: DW_TAG_typedef, name: "uLong", file: !5, line: 270, baseType: !18)
!18 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!19 = distinct !DISubprogram(name: "cm_zlib_zError", scope: !1, file: !1, line: 133, type: !20, isLocal: false, isDefinition: true, scopeLine: 135, isOptimized: false, variables: !2)
!20 = !DISubroutineType(types: !21)
!21 = !{!11, !22}
!22 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!23 = distinct !DISubprogram(name: "cm_zlib_zcalloc", scope: !1, file: !1, line: 300, type: !24, isLocal: false, isDefinition: true, scopeLine: 304, isOptimized: false, variables: !2)
!24 = !DISubroutineType(types: !25)
!25 = !{!4, !4, !26, !26}
!26 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!27 = distinct !DISubprogram(name: "cm_zlib_zcfree", scope: !1, file: !1, line: 310, type: !28, isLocal: false, isDefinition: true, scopeLine: 313, isOptimized: false, variables: !2)
!28 = !DISubroutineType(types: !29)
!29 = !{null, !4, !4}
!30 = !{!31}
!31 = !DIGlobalVariable(name: "cm_zlib_z_errmsg", scope: !0, file: !1, line: 14, type: !32, isLocal: false, isDefinition: true, variable: [10 x i8*]* @cm_zlib_z_errmsg)
!32 = !DICompositeType(tag: DW_TAG_array_type, baseType: !33, size: 640, align: 64, elements: !34)
!33 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !11)
!34 = !{!35}
!35 = !DISubrange(count: 10)
!36 = !{i32 2, !"Dwarf Version", i32 4}
!37 = !{i32 2, !"Debug Info Version", i32 3}
!38 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!39 = !DILocation(line: 29, column: 5, scope: !8)
!40 = !DILocalVariable(name: "flags", scope: !14, file: !1, line: 34, type: !17)
!41 = !DIExpression()
!42 = !DILocation(line: 34, column: 11, scope: !14)
!43 = !DILocation(line: 36, column: 11, scope: !14)
!44 = !DILocation(line: 39, column: 23, scope: !14)
!45 = !DILocation(line: 46, column: 23, scope: !14)
!46 = !DILocation(line: 52, column: 23, scope: !14)
!47 = !DILocation(line: 58, column: 23, scope: !14)
!48 = !DILocation(line: 112, column: 12, scope: !14)
!49 = !DILocation(line: 112, column: 5, scope: !14)
!50 = !DILocalVariable(name: "err", arg: 1, scope: !19, file: !1, line: 134, type: !22)
!51 = !DILocation(line: 134, column: 9, scope: !19)
!52 = !DILocation(line: 136, column: 12, scope: !19)
!53 = !DILocation(line: 136, column: 5, scope: !19)
!54 = !DILocalVariable(name: "opaque", arg: 1, scope: !23, file: !1, line: 301, type: !4)
!55 = !DILocation(line: 301, column: 12, scope: !23)
!56 = !DILocalVariable(name: "items", arg: 2, scope: !23, file: !1, line: 302, type: !26)
!57 = !DILocation(line: 302, column: 14, scope: !23)
!58 = !DILocalVariable(name: "size", arg: 3, scope: !23, file: !1, line: 303, type: !26)
!59 = !DILocation(line: 303, column: 14, scope: !23)
!60 = !DILocation(line: 305, column: 9, scope: !61)
!61 = distinct !DILexicalBlock(scope: !23, file: !1, line: 305, column: 9)
!62 = !DILocation(line: 305, column: 9, scope: !23)
!63 = !DILocation(line: 305, column: 26, scope: !64)
!64 = !DILexicalBlockFile(scope: !61, file: !1, discriminator: 1)
!65 = !DILocation(line: 305, column: 33, scope: !64)
!66 = !DILocation(line: 305, column: 31, scope: !64)
!67 = !DILocation(line: 305, column: 23, scope: !64)
!68 = !DILocation(line: 305, column: 17, scope: !64)
!69 = !DILocation(line: 306, column: 46, scope: !23)
!70 = !DILocation(line: 306, column: 54, scope: !23)
!71 = !DILocation(line: 306, column: 52, scope: !23)
!72 = !DILocation(line: 306, column: 39, scope: !23)
!73 = !DILocation(line: 306, column: 5, scope: !23)
!74 = !DILocalVariable(name: "opaque", arg: 1, scope: !27, file: !1, line: 311, type: !4)
!75 = !DILocation(line: 311, column: 12, scope: !27)
!76 = !DILocalVariable(name: "ptr", arg: 2, scope: !27, file: !1, line: 312, type: !4)
!77 = !DILocation(line: 312, column: 12, scope: !27)
!78 = !DILocation(line: 314, column: 10, scope: !27)
!79 = !DILocation(line: 314, column: 5, scope: !27)
!80 = !DILocation(line: 315, column: 9, scope: !81)
!81 = distinct !DILexicalBlock(scope: !27, file: !1, line: 315, column: 9)
!82 = !DILocation(line: 315, column: 9, scope: !27)
!83 = !DILocation(line: 315, column: 17, scope: !84)
!84 = !DILexicalBlockFile(scope: !81, file: !1, discriminator: 1)
!85 = !DILocation(line: 316, column: 1, scope: !27)
