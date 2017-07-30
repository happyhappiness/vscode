; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/inet_ntop.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [12 x i8] c"%d.%d.%d.%d\00", align 1

; Function Attrs: nounwind uwtable
define i8* @Curl_inet_ntop(i32 %af, i8* %src, i8* %buf, i64 %size) #0 !dbg !9 {
entry:
  %retval = alloca i8*, align 8
  %af.addr = alloca i32, align 4
  %src.addr = alloca i8*, align 8
  %buf.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  store i32 %af, i32* %af.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %af.addr, metadata !25, metadata !26), !dbg !27
  store i8* %src, i8** %src.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %src.addr, metadata !28, metadata !26), !dbg !29
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !30, metadata !26), !dbg !31
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !32, metadata !26), !dbg !33
  %0 = load i32, i32* %af.addr, align 4, !dbg !34
  switch i32 %0, label %sw.default [
    i32 2, label %sw.bb
  ], !dbg !35

sw.bb:                                            ; preds = %entry
  %1 = load i8*, i8** %src.addr, align 8, !dbg !36
  %2 = load i8*, i8** %buf.addr, align 8, !dbg !38
  %3 = load i64, i64* %size.addr, align 8, !dbg !39
  %call = call i8* @inet_ntop4(i8* %1, i8* %2, i64 %3), !dbg !40
  store i8* %call, i8** %retval, align 8, !dbg !41
  br label %return, !dbg !41

sw.default:                                       ; preds = %entry
  %call1 = call i32* @__errno_location() #1, !dbg !42
  store i32 97, i32* %call1, align 4, !dbg !42
  store i8* null, i8** %retval, align 8, !dbg !43
  br label %return, !dbg !43

return:                                           ; preds = %sw.default, %sw.bb
  %4 = load i8*, i8** %retval, align 8, !dbg !44
  ret i8* %4, !dbg !44
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal i8* @inet_ntop4(i8* %src, i8* %dst, i64 %size) #0 !dbg !19 {
entry:
  %retval = alloca i8*, align 8
  %src.addr = alloca i8*, align 8
  %dst.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %tmp = alloca [16 x i8], align 16
  %len = alloca i64, align 8
  store i8* %src, i8** %src.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %src.addr, metadata !45, metadata !26), !dbg !46
  store i8* %dst, i8** %dst.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dst.addr, metadata !47, metadata !26), !dbg !48
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !49, metadata !26), !dbg !50
  call void @llvm.dbg.declare(metadata [16 x i8]* %tmp, metadata !51, metadata !26), !dbg !55
  call void @llvm.dbg.declare(metadata i64* %len, metadata !56, metadata !26), !dbg !57
  br label %do.body, !dbg !58

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !59

do.end:                                           ; preds = %do.body
  %arrayidx = getelementptr inbounds [16 x i8], [16 x i8]* %tmp, i64 0, i64 0, !dbg !62
  store i8 0, i8* %arrayidx, align 16, !dbg !63
  %arraydecay = getelementptr inbounds [16 x i8], [16 x i8]* %tmp, i32 0, i32 0, !dbg !64
  %0 = load i8*, i8** %src.addr, align 8, !dbg !65
  %arrayidx2 = getelementptr inbounds i8, i8* %0, i64 0, !dbg !65
  %1 = load i8, i8* %arrayidx2, align 1, !dbg !65
  %conv = zext i8 %1 to i32, !dbg !66
  %and = and i32 %conv, 255, !dbg !67
  %2 = load i8*, i8** %src.addr, align 8, !dbg !68
  %arrayidx3 = getelementptr inbounds i8, i8* %2, i64 1, !dbg !68
  %3 = load i8, i8* %arrayidx3, align 1, !dbg !68
  %conv4 = zext i8 %3 to i32, !dbg !69
  %and5 = and i32 %conv4, 255, !dbg !70
  %4 = load i8*, i8** %src.addr, align 8, !dbg !71
  %arrayidx6 = getelementptr inbounds i8, i8* %4, i64 2, !dbg !71
  %5 = load i8, i8* %arrayidx6, align 1, !dbg !71
  %conv7 = zext i8 %5 to i32, !dbg !72
  %and8 = and i32 %conv7, 255, !dbg !73
  %6 = load i8*, i8** %src.addr, align 8, !dbg !74
  %arrayidx9 = getelementptr inbounds i8, i8* %6, i64 3, !dbg !74
  %7 = load i8, i8* %arrayidx9, align 1, !dbg !74
  %conv10 = zext i8 %7 to i32, !dbg !75
  %and11 = and i32 %conv10, 255, !dbg !76
  %call = call i32 (i8*, i64, i8*, ...) @curl_msnprintf(i8* %arraydecay, i64 16, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str, i32 0, i32 0), i32 %and, i32 %and5, i32 %and8, i32 %and11), !dbg !77
  %arraydecay12 = getelementptr inbounds [16 x i8], [16 x i8]* %tmp, i32 0, i32 0, !dbg !78
  %call13 = call i64 @strlen(i8* %arraydecay12) #6, !dbg !79
  store i64 %call13, i64* %len, align 8, !dbg !80
  %8 = load i64, i64* %len, align 8, !dbg !81
  %cmp = icmp eq i64 %8, 0, !dbg !83
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !84

lor.lhs.false:                                    ; preds = %do.end
  %9 = load i64, i64* %len, align 8, !dbg !85
  %10 = load i64, i64* %size.addr, align 8, !dbg !87
  %cmp15 = icmp uge i64 %9, %10, !dbg !88
  br i1 %cmp15, label %if.then, label %if.end, !dbg !89

if.then:                                          ; preds = %lor.lhs.false, %do.end
  %call17 = call i32* @__errno_location() #1, !dbg !90
  store i32 28, i32* %call17, align 4, !dbg !90
  store i8* null, i8** %retval, align 8, !dbg !92
  br label %return, !dbg !92

if.end:                                           ; preds = %lor.lhs.false
  %11 = load i8*, i8** %dst.addr, align 8, !dbg !93
  %arraydecay18 = getelementptr inbounds [16 x i8], [16 x i8]* %tmp, i32 0, i32 0, !dbg !94
  %call19 = call i8* @strcpy(i8* %11, i8* %arraydecay18) #7, !dbg !95
  %12 = load i8*, i8** %dst.addr, align 8, !dbg !96
  store i8* %12, i8** %retval, align 8, !dbg !97
  br label %return, !dbg !97

return:                                           ; preds = %if.end, %if.then
  %13 = load i8*, i8** %retval, align 8, !dbg !98
  ret i8* %13, !dbg !98
}

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #2

declare i32 @curl_msnprintf(i8*, i64, i8*, ...) #3

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #5

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readonly }
attributes #7 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!22, !23}
!llvm.ident = !{!24}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !8)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/inet_ntop.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{}
!3 = !{!4, !7, !6}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !6)
!6 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = !{!9, !19}
!9 = distinct !DISubprogram(name: "Curl_inet_ntop", scope: !1, file: !1, line: 183, type: !10, isLocal: false, isDefinition: true, scopeLine: 184, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!10 = !DISubroutineType(types: !11)
!11 = !{!12, !7, !14, !12, !16}
!12 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !13, size: 64, align: 64)
!13 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!14 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !15, size: 64, align: 64)
!15 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!16 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !17, line: 62, baseType: !18)
!17 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!18 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!19 = distinct !DISubprogram(name: "inet_ntop4", scope: !1, file: !1, line: 50, type: !20, isLocal: true, isDefinition: true, scopeLine: 51, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!20 = !DISubroutineType(types: !21)
!21 = !{!12, !4, !12, !16}
!22 = !{i32 2, !"Dwarf Version", i32 4}
!23 = !{i32 2, !"Debug Info Version", i32 3}
!24 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!25 = !DILocalVariable(name: "af", arg: 1, scope: !9, file: !1, line: 183, type: !7)
!26 = !DIExpression()
!27 = !DILocation(line: 183, column: 26, scope: !9)
!28 = !DILocalVariable(name: "src", arg: 2, scope: !9, file: !1, line: 183, type: !14)
!29 = !DILocation(line: 183, column: 42, scope: !9)
!30 = !DILocalVariable(name: "buf", arg: 3, scope: !9, file: !1, line: 183, type: !12)
!31 = !DILocation(line: 183, column: 53, scope: !9)
!32 = !DILocalVariable(name: "size", arg: 4, scope: !9, file: !1, line: 183, type: !16)
!33 = !DILocation(line: 183, column: 65, scope: !9)
!34 = !DILocation(line: 185, column: 10, scope: !9)
!35 = !DILocation(line: 185, column: 3, scope: !9)
!36 = !DILocation(line: 187, column: 46, scope: !37)
!37 = distinct !DILexicalBlock(scope: !9, file: !1, line: 185, column: 14)
!38 = !DILocation(line: 187, column: 51, scope: !37)
!39 = !DILocation(line: 187, column: 56, scope: !37)
!40 = !DILocation(line: 187, column: 12, scope: !37)
!41 = !DILocation(line: 187, column: 5, scope: !37)
!42 = !DILocation(line: 193, column: 5, scope: !37)
!43 = !DILocation(line: 194, column: 5, scope: !37)
!44 = !DILocation(line: 196, column: 1, scope: !9)
!45 = !DILocalVariable(name: "src", arg: 1, scope: !19, file: !1, line: 50, type: !4)
!46 = !DILocation(line: 50, column: 47, scope: !19)
!47 = !DILocalVariable(name: "dst", arg: 2, scope: !19, file: !1, line: 50, type: !12)
!48 = !DILocation(line: 50, column: 58, scope: !19)
!49 = !DILocalVariable(name: "size", arg: 3, scope: !19, file: !1, line: 50, type: !16)
!50 = !DILocation(line: 50, column: 70, scope: !19)
!51 = !DILocalVariable(name: "tmp", scope: !19, file: !1, line: 52, type: !52)
!52 = !DICompositeType(tag: DW_TAG_array_type, baseType: !13, size: 128, align: 8, elements: !53)
!53 = !{!54}
!54 = !DISubrange(count: 16)
!55 = !DILocation(line: 52, column: 8, scope: !19)
!56 = !DILocalVariable(name: "len", scope: !19, file: !1, line: 53, type: !16)
!57 = !DILocation(line: 53, column: 10, scope: !19)
!58 = !DILocation(line: 55, column: 3, scope: !19)
!59 = !DILocation(line: 55, column: 3, scope: !60)
!60 = !DILexicalBlockFile(scope: !61, file: !1, discriminator: 1)
!61 = distinct !DILexicalBlock(scope: !19, file: !1, line: 55, column: 3)
!62 = !DILocation(line: 57, column: 3, scope: !19)
!63 = !DILocation(line: 57, column: 10, scope: !19)
!64 = !DILocation(line: 58, column: 18, scope: !19)
!65 = !DILocation(line: 59, column: 40, scope: !19)
!66 = !DILocation(line: 59, column: 19, scope: !19)
!67 = !DILocation(line: 59, column: 49, scope: !19)
!68 = !DILocation(line: 60, column: 40, scope: !19)
!69 = !DILocation(line: 60, column: 19, scope: !19)
!70 = !DILocation(line: 60, column: 49, scope: !19)
!71 = !DILocation(line: 61, column: 40, scope: !19)
!72 = !DILocation(line: 61, column: 19, scope: !19)
!73 = !DILocation(line: 61, column: 49, scope: !19)
!74 = !DILocation(line: 62, column: 40, scope: !19)
!75 = !DILocation(line: 62, column: 19, scope: !19)
!76 = !DILocation(line: 62, column: 49, scope: !19)
!77 = !DILocation(line: 58, column: 9, scope: !19)
!78 = !DILocation(line: 64, column: 16, scope: !19)
!79 = !DILocation(line: 64, column: 9, scope: !19)
!80 = !DILocation(line: 64, column: 7, scope: !19)
!81 = !DILocation(line: 65, column: 6, scope: !82)
!82 = distinct !DILexicalBlock(scope: !19, file: !1, line: 65, column: 6)
!83 = !DILocation(line: 65, column: 10, scope: !82)
!84 = !DILocation(line: 65, column: 15, scope: !82)
!85 = !DILocation(line: 65, column: 18, scope: !86)
!86 = !DILexicalBlockFile(scope: !82, file: !1, discriminator: 1)
!87 = !DILocation(line: 65, column: 25, scope: !86)
!88 = !DILocation(line: 65, column: 22, scope: !86)
!89 = !DILocation(line: 65, column: 6, scope: !86)
!90 = !DILocation(line: 66, column: 5, scope: !91)
!91 = distinct !DILexicalBlock(scope: !82, file: !1, line: 65, column: 31)
!92 = !DILocation(line: 67, column: 5, scope: !91)
!93 = !DILocation(line: 69, column: 10, scope: !19)
!94 = !DILocation(line: 69, column: 15, scope: !19)
!95 = !DILocation(line: 69, column: 3, scope: !19)
!96 = !DILocation(line: 70, column: 10, scope: !19)
!97 = !DILocation(line: 70, column: 3, scope: !19)
!98 = !DILocation(line: 71, column: 1, scope: !19)
