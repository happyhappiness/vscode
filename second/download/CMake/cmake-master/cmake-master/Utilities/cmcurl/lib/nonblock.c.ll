; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/nonblock.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @curlx_nonblock(i32 %sockfd, i32 %nonblock) #0 !dbg !4 {
entry:
  %retval = alloca i32, align 4
  %sockfd.addr = alloca i32, align 4
  %nonblock.addr = alloca i32, align 4
  %flags = alloca i32, align 4
  store i32 %sockfd, i32* %sockfd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sockfd.addr, metadata !13, metadata !14), !dbg !15
  store i32 %nonblock, i32* %nonblock.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nonblock.addr, metadata !16, metadata !14), !dbg !17
  call void @llvm.dbg.declare(metadata i32* %flags, metadata !18, metadata !14), !dbg !19
  %0 = load i32, i32* %sockfd.addr, align 4, !dbg !20
  %call = call i32 (i32, i32, ...) @fcntl(i32 %0, i32 3, i32 0), !dbg !21
  store i32 %call, i32* %flags, align 4, !dbg !22
  %1 = load i32, i32* %nonblock.addr, align 4, !dbg !23
  %tobool = icmp ne i32 %1, 0, !dbg !23
  br i1 %tobool, label %if.then, label %if.end, !dbg !25

if.then:                                          ; preds = %entry
  %2 = load i32, i32* %sockfd.addr, align 4, !dbg !26
  %3 = load i32, i32* %flags, align 4, !dbg !27
  %or = or i32 %3, 2048, !dbg !28
  %call1 = call i32 (i32, i32, ...) @fcntl(i32 %2, i32 4, i32 %or), !dbg !29
  store i32 %call1, i32* %retval, align 4, !dbg !30
  br label %return, !dbg !30

if.end:                                           ; preds = %entry
  %4 = load i32, i32* %sockfd.addr, align 4, !dbg !31
  %5 = load i32, i32* %flags, align 4, !dbg !32
  %and = and i32 %5, -2049, !dbg !33
  %call2 = call i32 (i32, i32, ...) @fcntl(i32 %4, i32 4, i32 %and), !dbg !34
  store i32 %call2, i32* %retval, align 4, !dbg !35
  br label %return, !dbg !35

return:                                           ; preds = %if.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !36
  ret i32 %6, !dbg !36
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @fcntl(i32, i32, ...) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!10, !11}
!llvm.ident = !{!12}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/nonblock.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "curlx_nonblock", scope: !1, file: !1, line: 47, type: !5, isLocal: false, isDefinition: true, scopeLine: 49, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !8, !7}
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_socket_t", file: !9, line: 131, baseType: !7)
!9 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curl.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!10 = !{i32 2, !"Dwarf Version", i32 4}
!11 = !{i32 2, !"Debug Info Version", i32 3}
!12 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!13 = !DILocalVariable(name: "sockfd", arg: 1, scope: !4, file: !1, line: 47, type: !8)
!14 = !DIExpression()
!15 = !DILocation(line: 47, column: 34, scope: !4)
!16 = !DILocalVariable(name: "nonblock", arg: 2, scope: !4, file: !1, line: 48, type: !7)
!17 = !DILocation(line: 48, column: 24, scope: !4)
!18 = !DILocalVariable(name: "flags", scope: !4, file: !1, line: 57, type: !7)
!19 = !DILocation(line: 57, column: 7, scope: !4)
!20 = !DILocation(line: 58, column: 18, scope: !4)
!21 = !DILocation(line: 58, column: 11, scope: !4)
!22 = !DILocation(line: 58, column: 9, scope: !4)
!23 = !DILocation(line: 59, column: 6, scope: !24)
!24 = distinct !DILexicalBlock(scope: !4, file: !1, line: 59, column: 6)
!25 = !DILocation(line: 59, column: 6, scope: !4)
!26 = !DILocation(line: 60, column: 19, scope: !24)
!27 = !DILocation(line: 60, column: 36, scope: !24)
!28 = !DILocation(line: 60, column: 42, scope: !24)
!29 = !DILocation(line: 60, column: 12, scope: !24)
!30 = !DILocation(line: 60, column: 5, scope: !24)
!31 = !DILocation(line: 61, column: 17, scope: !4)
!32 = !DILocation(line: 61, column: 34, scope: !4)
!33 = !DILocation(line: 61, column: 40, scope: !4)
!34 = !DILocation(line: 61, column: 10, scope: !4)
!35 = !DILocation(line: 61, column: 3, scope: !4)
!36 = !DILocation(line: 90, column: 1, scope: !4)
