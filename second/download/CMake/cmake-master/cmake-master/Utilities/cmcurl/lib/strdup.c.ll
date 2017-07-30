; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/strdup.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@Curl_cmalloc = external global i8* (i64)*, align 8
@Curl_crealloc = external global i8* (i8*, i64)*, align 8
@Curl_cfree = external global void (i8*)*, align 8

; Function Attrs: nounwind uwtable
define i8* @Curl_memdup(i8* %src, i64 %length) #0 !dbg !6 {
entry:
  %retval = alloca i8*, align 8
  %src.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  %buffer = alloca i8*, align 8
  store i8* %src, i8** %src.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %src.addr, metadata !20, metadata !21), !dbg !22
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !23, metadata !21), !dbg !24
  call void @llvm.dbg.declare(metadata i8** %buffer, metadata !25, metadata !21), !dbg !26
  %0 = load i8* (i64)*, i8* (i64)** @Curl_cmalloc, align 8, !dbg !27
  %1 = load i64, i64* %length.addr, align 8, !dbg !27
  %call = call i8* %0(i64 %1), !dbg !27
  store i8* %call, i8** %buffer, align 8, !dbg !26
  %2 = load i8*, i8** %buffer, align 8, !dbg !28
  %tobool = icmp ne i8* %2, null, !dbg !28
  br i1 %tobool, label %if.end, label %if.then, !dbg !30

if.then:                                          ; preds = %entry
  store i8* null, i8** %retval, align 8, !dbg !31
  br label %return, !dbg !31

if.end:                                           ; preds = %entry
  %3 = load i8*, i8** %buffer, align 8, !dbg !32
  %4 = load i8*, i8** %src.addr, align 8, !dbg !33
  %5 = load i64, i64* %length.addr, align 8, !dbg !34
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %3, i8* %4, i64 %5, i32 1, i1 false), !dbg !35
  %6 = load i8*, i8** %buffer, align 8, !dbg !36
  store i8* %6, i8** %retval, align 8, !dbg !37
  br label %return, !dbg !37

return:                                           ; preds = %if.end, %if.then
  %7 = load i8*, i8** %retval, align 8, !dbg !38
  ret i8* %7, !dbg !38
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #2

; Function Attrs: nounwind uwtable
define i8* @Curl_saferealloc(i8* %ptr, i64 %size) #0 !dbg !14 {
entry:
  %ptr.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %datap = alloca i8*, align 8
  store i8* %ptr, i8** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr.addr, metadata !39, metadata !21), !dbg !40
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !41, metadata !21), !dbg !42
  call void @llvm.dbg.declare(metadata i8** %datap, metadata !43, metadata !21), !dbg !44
  %0 = load i8* (i8*, i64)*, i8* (i8*, i64)** @Curl_crealloc, align 8, !dbg !45
  %1 = load i8*, i8** %ptr.addr, align 8, !dbg !45
  %2 = load i64, i64* %size.addr, align 8, !dbg !45
  %call = call i8* %0(i8* %1, i64 %2), !dbg !45
  store i8* %call, i8** %datap, align 8, !dbg !44
  %3 = load i64, i64* %size.addr, align 8, !dbg !46
  %tobool = icmp ne i64 %3, 0, !dbg !46
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !48

land.lhs.true:                                    ; preds = %entry
  %4 = load i8*, i8** %datap, align 8, !dbg !49
  %tobool1 = icmp ne i8* %4, null, !dbg !49
  br i1 %tobool1, label %if.end, label %if.then, !dbg !51

if.then:                                          ; preds = %land.lhs.true
  %5 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !52
  %6 = load i8*, i8** %ptr.addr, align 8, !dbg !52
  call void %5(i8* %6), !dbg !52
  br label %if.end, !dbg !52

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  %7 = load i8*, i8** %datap, align 8, !dbg !53
  ret i8* %7, !dbg !54
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { argmemonly nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!17, !18}
!llvm.ident = !{!19}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !5)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/strdup.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{}
!3 = !{!4}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !{!6, !14}
!6 = distinct !DISubprogram(name: "Curl_memdup", scope: !1, file: !1, line: 68, type: !7, isLocal: false, isDefinition: true, scopeLine: 69, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!7 = !DISubroutineType(types: !8)
!8 = !{!4, !9, !11}
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!11 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !12, line: 62, baseType: !13)
!12 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!13 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!14 = distinct !DISubprogram(name: "Curl_saferealloc", scope: !1, file: !1, line: 93, type: !15, isLocal: false, isDefinition: true, scopeLine: 94, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!15 = !DISubroutineType(types: !16)
!16 = !{!4, !4, !11}
!17 = !{i32 2, !"Dwarf Version", i32 4}
!18 = !{i32 2, !"Debug Info Version", i32 3}
!19 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!20 = !DILocalVariable(name: "src", arg: 1, scope: !6, file: !1, line: 68, type: !9)
!21 = !DIExpression()
!22 = !DILocation(line: 68, column: 31, scope: !6)
!23 = !DILocalVariable(name: "length", arg: 2, scope: !6, file: !1, line: 68, type: !11)
!24 = !DILocation(line: 68, column: 43, scope: !6)
!25 = !DILocalVariable(name: "buffer", scope: !6, file: !1, line: 70, type: !4)
!26 = !DILocation(line: 70, column: 9, scope: !6)
!27 = !DILocation(line: 70, column: 18, scope: !6)
!28 = !DILocation(line: 71, column: 7, scope: !29)
!29 = distinct !DILexicalBlock(scope: !6, file: !1, line: 71, column: 6)
!30 = !DILocation(line: 71, column: 6, scope: !6)
!31 = !DILocation(line: 72, column: 5, scope: !29)
!32 = !DILocation(line: 74, column: 10, scope: !6)
!33 = !DILocation(line: 74, column: 18, scope: !6)
!34 = !DILocation(line: 74, column: 23, scope: !6)
!35 = !DILocation(line: 74, column: 3, scope: !6)
!36 = !DILocation(line: 76, column: 10, scope: !6)
!37 = !DILocation(line: 76, column: 3, scope: !6)
!38 = !DILocation(line: 77, column: 1, scope: !6)
!39 = !DILocalVariable(name: "ptr", arg: 1, scope: !14, file: !1, line: 93, type: !4)
!40 = !DILocation(line: 93, column: 30, scope: !14)
!41 = !DILocalVariable(name: "size", arg: 2, scope: !14, file: !1, line: 93, type: !11)
!42 = !DILocation(line: 93, column: 42, scope: !14)
!43 = !DILocalVariable(name: "datap", scope: !14, file: !1, line: 95, type: !4)
!44 = !DILocation(line: 95, column: 9, scope: !14)
!45 = !DILocation(line: 95, column: 17, scope: !14)
!46 = !DILocation(line: 96, column: 6, scope: !47)
!47 = distinct !DILexicalBlock(scope: !14, file: !1, line: 96, column: 6)
!48 = !DILocation(line: 96, column: 11, scope: !47)
!49 = !DILocation(line: 96, column: 15, scope: !50)
!50 = !DILexicalBlockFile(scope: !47, file: !1, discriminator: 1)
!51 = !DILocation(line: 96, column: 6, scope: !50)
!52 = !DILocation(line: 98, column: 5, scope: !47)
!53 = !DILocation(line: 99, column: 10, scope: !14)
!54 = !DILocation(line: 99, column: 3, scope: !14)
